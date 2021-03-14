;
; The dinosaur game ('The dino says Graaah!')
;
; Sensors and microsystem electronics
; Year: 2017-2018
; Authors : Remco Royen & Johan Jacobs
;
; main.asm

.INCLUDE "m328pdef.INC"			; Load addresses of (I/O) registers

.def mulLSB = R0
.def mulMSB = R1

.def memoryByteRegister = R2

.def maxNmbrOfCacti = R3		; Maximum number of Cacti that are allowed to move on the screen in this level
.def nmbrOfCacti = R4			; Actual number of cacti moving on the screen

.def randomNumber = R5 ;		; A pseudo-random number by use of LFSR, is computed by calling Random

; Shift registers for the PRNG
.def randomSR1 = R6
.def randomSR2 = R7
.def randomSR3 = R8
.def randomSR4 = R9
.def randomSR5 = R10

.def modeCounter = R11			; Keeps track of when is needed to change mode or to increase maxNmbrOfCacti
.def buzzerCounter = R12		; Keeps track of how long the buzzer is already buzzing

.def passToFunctionRegister = R13 ; Is used in random to pass a value to a function

.def timer0ResetCounter = R14	; Count to 100 before increasing speed of dinosaur jumps
.def timer0ResetVal = R15		; Value to increase TCNT0 over time (faster interrupts)

.def counter = R16				; Register that serves for all kind of counter actions
.def illuminatedRow = R17		; Indicates the row that will be illuminated
.def tempRegister = R18			; Temporary register for short-time savings

.def flags = R19				; bit 0 = Collision (set = collision) | bit 1 = normalOrExtreme mode (set = extreme)
								; bit 2 = Buzzersound (set = buzzer on) | bit 3 = keyBoardPressed (set = button pressed)
								; bit 4 = Insane mode (set = insane)

.def dinoJumping = R21
.def registerBitCounter = R22

.def gameState = R23			; = 0x00 -> Playing 
								; = 0x01 -> Game Over
								; = 0xFF -> 'Menu': Wait for button to play

.def xpos = R24		
.def ypos = R25

; R26/R27 X pointer is used to point to addresses in memory
; R28/R29 Y pointer is used to speed up the cacti
; R30/R31 Z pointer is used to keep score: The word is divided in 4 4-bit long chunks: for example 5809 : part 1 = 5, part 2 = 8, part 3 = 0, part 4 = 9

.equ bufferStartAddress = 0x0100
.equ cactusMemory = 0x0300
.equ dinoMemory = 0x0350

.equ initialTimeValueBuzzer = 185
.equ buzzerDuration = 255

.equ maxValueCounter0 = 255
.equ maxValueCounter1 = 3
.equ maxValueCounter2 = 0

.ORG 0x0000
RJMP startUp

.ORG 0x0012
RJMP Timer2OverflowInterrupt

.ORG 0x001A
RJMP Timer1OverflowInterrupt

.ORG 0x0020
RJMP Timer0OverflowInterrupt

.include "coreFunctions.INC"
.include "keyboard.INC"
.include "drawingFunctions.INC"
.include "drawPatterns.INC"
.include "macros.INC"
.include "random.INC"
.include "interrupts.INC"

startUp:
	RCALL initGame

main:

	; STATE MACHINE
	CPI gameState,0
	BRNE notPlaying
		; STATE 0: PLAYING
		RCALL clearBuffer
		RCALL drawCactus
		RCALL drawDino
		RCALL drawScore
		RJMP restOfMain

	notPlaying:
	CPI gameState,0xFF
	BRNE gameOver
		; STATE FF: MENU
		RCALL clearBuffer
		RCALL drawDino
		RJMP restOfMain

	gameOver:
		; STATE 1: GAME OVER
		MOV tempregister, buzzerCounter
		CPI tempregister,buzzerDuration
		BRLO restOfMain
		CBR flags,0b00000100	; Clear buzzer flag
		CBI PORTB,1				; Make sure buzzer is 'off' after use

	restOfMain:
	RCALL checkKeyboard
	RCALL flushMemory
	RCALL collisionHandler ; Check if collision has happened and react
	RJMP main

initGame:
// Initiates all the game parameters: variables, in- and output pins, timers, interrupts and prepares the screen
// Registers changed: gameState, nmbrOfCacti, maxNmbrOfCacti, flags, dinoJumping, timer0ResetCounter, timer0ResetVal, tempregister, Y-pointer, Z-pointer
// Functions called: clearBuffer, initDino, addCactus

	; To avoid flickering
	RCALL clearBuffer

	; Set variables
	SER gameState ; Begin in idle state

	CLR nmbrOfCacti ; No cacti drawn
	CLR maxNmbrOfCacti
	INC maxNmbrOfCacti ; First level only one cactus

	CLR dinoJumping ; Dino starts not jumping
	CLR modeCounter
	CLR ZH ; Score set to zero
	CLR ZL ; Score set to zero

	CLR flags

	CLR timer0ResetCounter
	CLR timer0ResetVal
	
	; Configure output pin PB1 (Buzzer)
	SBI DDRB,1					; Pin PB1 is an output
	CBI PORTB,1					; Output low => initial condition low!

	; Configure output pin PB3 (Data input screen)
	SBI DDRB,3					; Pin PB3 is an output
	CBI PORTB,3					; Output low => initial condition low!

	; Configure output pin PB4 (Screen latching and enable'ing)
	SBI DDRB,4					; Pin PB4 is an output
	CBI PORTB,4					; Output low => initial condition low!

	; Configure output pin PB5 (Clock Screen)
	SBI DDRB,5					; Pin PB5 is an output
	CBI PORTB,5					; Output low => initial condition low!

	; Configure a LED as output (to test things)
	SBI DDRC,2					; Pin PC2 is an output 
	SBI PORTC,2					; Output Vcc => upper LED turned off!

	// Timer0 (8 bit timer) initialisation
	LDI tempRegister, 0x0	; Select normal counter mode
	OUT TCCR0A, tempRegister
	
	LDI tempRegister, 0x05	; Set timer0 prescaler to 1024
	OUT TCCR0B,tempRegister	;set correct ‘reload values’ 256 - 16 000 000/1024/62 = 4 (after rounding)

	LDI tempRegister, 60
	MOV timer0ResetVal, tempRegister
	OUT TCNT0,timer0ResetVal		; TCNT0 = Timer/counter

	// Timer1 (16 bit timer) initialisation

	LDI tempRegister, 0x0	; Select normal counter mode
	STS TCCR1A, tempRegister
	LDI tempRegister, 0x03	; Set timer1 prescaler to 64 == 011, 1024 == 101 (Important: this is different for 8 bit timer)
	STS TCCR1B,tempRegister

		/* Initial timer value will be 5 Hz. As the game progresses, the frequency at which the cacti move should be increased. We will do this by adding an immediate to the Y registers and storing this in TCNT1.  */
		; Prescaler 64: 65536 - 16 000 000/64/5 = 65536 - 50000 = 15536 => 00111100 10110000
	LDI YH, 0b00111100
	LDI YL, 0b10110000

	STS TCNT1H, YH
	STS TCNT1L, YL

	// Timer2 (8 bit timer) initialisation

	LDI tempRegister, 0x0	; Select normal counter mode
	STS TCCR2A, tempRegister
	LDI tempRegister, 0x07	; Set timer2 prescaler to 1024 == 111, 
	STS TCCR2B,tempRegister
	LDI tempRegister, 0		; Set correct ‘reload values’ 256 - 16 000 000/1024/61 = 0 (after rounding)
	STS TCNT2,tempRegister

	// Enable interrupts

	SEI									; (SEI: global interrupt enable)
	LDI tempRegister, 1
	STS TIMSK1, tempRegister			; set peripheral interrupt flag
	STS TIMSK0, tempRegister
	STS TIMSK2, tempRegister

	// Prepare Screen

	RCALL initDino ; Initialize dinosaur
	RCALL addCactus ; Prepare first cactus
	RET