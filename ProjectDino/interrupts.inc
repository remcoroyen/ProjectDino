;
; The dinosaur game ('The dino says Graaah!')
;
; Sensors and microsystem electronics
; Year: 2017-2018
; Authors : Remco Royen & Johan Jacobs
;
; interrupts.inc

Timer0OverflowInterrupt:
// Check if jump key (button 7) was pressed. If it has been pressed, the dinosaur will move up, float, and move down. 
// If you keep the button pressed for a longer duration, the dinosaur will float a bit longer.
// Changed registers: dinoJumping, 
// Functions called: /
	PUSH XH
	PUSH XL
	PUSH tempRegister
	IN tempRegister, SREG
	PUSH tempRegister

	// Reset timer values 
	OUT TCNT0,timer0ResetVal

	// Every 5 times the interrupt is called, the dinosaur will move up or down. Starting value for dinoJumping is at 4 to immediately move up the first moment the button is pressed.
	CPI dinoJumping, 4
	BRLO timer0Ret						; Branch if Lower

	INC dinoJumping

	CPI dinoJumping, 31
	BRSH checkFloat						; if dinoJumping is higher than 30, it will have to stay up (if keyboard is pressed) or come back down

	LDI tempRegister,5
	MOD dinoJumping,tempRegister		; Result will be in tempRegister such that we don't overwrite dinoJumping
	CPI tempRegister,0
	BREQ dinoJump
	RJMP timer0Ret						; If you don't have to go up, just return (already checked for float and drop earlier)

	// Check if we're holding down the keyboard (to jump for a longer duration)
	checkFloat:
		SBRS flags,3
		RJMP checkDropping
	
	dinoFloat:
		CPI dinoJumping,200				; This is the maximal amount of time the dinosaur will float
		BRLO timer0Ret

	
	checkDropping:
		LDI tempRegister,5
		MOD dinoJumping,tempRegister	; Result will be in tempRegister such that we don't overwrite dinoJumping
		CPI tempRegister,0
		BREQ dinoDrop
		RJMP timer0Ret					; Skip everything in other cases

	// Move dino 1 pixel up
	dinoJump:
		LDI XH, HIGH(dinoMemory)
		LDI XL, LOW(dinoMemory+1)		; The xposition of the dinosaur never changes, so we can just load the address of the y position and change that value
		LD tempRegister, X				; Load old ypos
		DEC tempRegister				; Decrease ypos (go up)
		ST X,tempRegister				; Store ypos
		RJMP timer0Ret

	// Move dino 1 pixel down
	dinoDrop:
		LDI XH, HIGH(dinoMemory)
		LDI XL, LOW(dinoMemory+1)		; The xposition of the dinosaur never changes, so we can just load the address of the y position and change that value
		LD tempRegister, X				; Load old ypos
		INC tempRegister				; Increase ypos (go down)
		ST X,tempRegister				; Store ypos

		// Clear dinoJumping if dino has landed (if its y position is equal to 8)
		CPI tempRegister, 8			
		BRNE timer0Ret
		CLR dinoJumping

	timer0Ret:
		POP tempRegister
		OUT SREG, tempRegister
		POP tempRegister
		POP XL
		POP XH
		RETI

Timer1OverflowInterrupt:
// Timer 1 (16 bit) is used to control the game logic. It makes sure the cacti move towards the dinosaur, it updates the score, it mirrors the screen at certain moments and it inverts the LEDS at certain moments.
// Changed registers: maxNmbrOfCacti, modeCounter
// Functions called: moveCactus, updateScore, newCactusOrNot, inverseDinoPos
	PUSH tempRegister
	IN tempRegister, SREG
	PUSH tempRegister
	PUSH counter			; counter is here used as a temporary variable

	// Reset timer values: The current speed of the cacti is saved in the Y-registers
	STS TCNT1H, YH
	STS TCNT1L, YL

	RCALL moveCactus		; Move the cacti
	RCALL updateScore		; Increments the score by one

	CPI gameState,0
	BRNE timer1Ret			; The following code is only executed when gameState = 'playing'
	RCALL newCactusOrNot	; Make decision about new cactus or not

	CLR tempregister
	CP modeCounter,tempregister
	BREQ modeCounterInc

	LDI tempregister,50
	MOD modeCounter,tempregister
	CPI tempregister,0		; Every 50 movements, increase maxNmbrOfCacti
	BRNE modeCounterInc
		INC maxNmbrOfCacti
		LDI tempregister, 0b00010000
		EOR flags, tempregister
		RCALL inverseDinoPos

	LDI tempregister,100
	MOD modeCounter,tempregister
	CPI tempregister,0		; Every 100 movements, change normal/extreme
	BRNE modeCounterInc
		LDI tempregister, 0b00000010
		EOR flags, tempregister
		CLR modeCounter
		RJMP timer1Ret

	modeCounterInc:
		INC modeCounter

	timer1Ret:
		POP counter
		POP tempRegister
		OUT SREG, tempRegister
		POP tempRegister
		RETI


Timer2OverflowInterrupt:
// Timer2 is used to increase the speed of the cacti at a constant rate or to sound the buzzer when you lose the game.
// Changed registers: YL, timer0ResetVal, buzzerCounter
// Functions called: /
	PUSH tempRegister
	IN tempRegister, SREG
	PUSH tempRegister

	// Reset timer values
	LDI tempRegister, 0
	STS TCNT2,tempRegister

	LDI tempRegister, 180
	CP timer0ResetVal, tempRegister			; Check if maximum jump speed was reached
	BRSH timer2Buzzer

	INC timer0ResetCounter
	ADIW YL, 10								; The Y registers will contain the reset values of the 16 bit timer. Increasing YL means the interrupt is called more often and the cacti speed increases

	INC timer0ResetCounter
	LDI tempRegister, 30						; Update the dinosaur movement (with the 8 bit timer) at roughly the same rate as the cacti speed
	CP timer0ResetCounter, tempRegister
	BRLO timer2Buzzer
	INC timer0ResetVal
	CLR timer0ResetCounter

	timer2Buzzer:

		SBRS flags,2
		RJMP timer2Ret

		LDI tempRegister, initialTimeValueBuzzer
		STS TCNT2,tempRegister
		SBI PINB,1
		INC buzzerCounter		; To limit the time the buzzer buzzes

	timer2Ret:
	POP tempRegister
	OUT SREG, tempRegister
	POP tempRegister
	RETI