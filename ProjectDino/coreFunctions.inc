;
; The dinosaur game ('The dino says Graaah!')
;
; Sensors and microsystem electronics
; Year: 2017-2018
; Authors : Remco Royen & Johan Jacobs
;
; coreFunctions.inc

waitingLoop:
// A loop that can be used to wait for a certain time (e.g. Latching time)
// Changed registers: /
	PUSH tempRegister
	PUSH counter

	CLR tempRegister
	CLR counter
	outerLoop:
		INC tempRegister
		CPI tempRegister,maxValueCounter0
		BRNE outerLoop

		middleLoop:
			CLR tempRegister
			INC counter
			CPI counter,maxValueCounter1
			BRNE outerLoop	
	finishLoop:

	POP counter
	POP tempRegister
RET

collisionHandler:
// Checks if collision has occured and handles the reaction on the collision
// Changed registers: flags, gameState, buzzerCounter
// Called functions: clearBuffer, drawGameOver, drawScore
	PUSH tempregister
	
	SBRS flags,0
	RJMP collisionRet

	CBR flags,1 ; Clear the collision flag
	CBR flags,0b00000010 ; Go back to normal mode from Extreme for game over screen
	CBR flags,0b00010000 ; Go back to normal mode from Insane for game over screen
	RCALL clearBuffer	; Clear the screen such that not a new collision would happen (goal is to remove cacti)
	RCALL drawGameOver
	LDI gameState,1 ; Go to Game Over state
	RCALL drawScore
	SBR flags,0b00000100 ; Set the buzzersound flag
	CLR buzzerCounter

	; Re-use Timer 2

	LDI tempRegister, 0x0	; Select normal counter mode
	STS TCCR2A, tempRegister
	LDI tempRegister, 0x06	; Set timer2 prescaler to 256 
	STS TCCR2B,tempRegister
	LDI tempRegister, initialTimeValueBuzzer
	STS TCNT2,tempRegister

	collisionRet:
	POP tempregister
	RET

addCactus:
// Adds a new cactus to cactusMemory
// Changed registers: nmbrOfCacti
	PUSH xpos
	PUSH ypos
	PUSH tempregister
	PUSH XH
	PUSH XL

	LDI XH, HIGH(cactusMemory)			// Point to start of cactusMemory
	LDI XL, LOW(cactusMemory)

	MOV tempregister, nmbrOfCacti
	LSL tempregister

	ADD XL , tempregister

	LDI xpos, 38							// xpos of cactus
	ST X+, xpos
	LDI ypos, 10							// ypos of cactus
	ST X, ypos

	INC nmbrOfCacti

	POP XL
	POP XH
	POP tempregister
	POP ypos
	POP xpos
	RET

moveCactus:
// Changes the coordinates in Cactus memory. The coordinates are always moved as in normal mode, the difference between insane and normal mode is made in drawCacti
// If the cactus is at the end, it deletes the cactus and puts a new one at starting position
// Changed registers: nmbrOfCacti
// Called functions: deleteFirstCactus

	PUSH xpos
	PUSH tempRegister
	PUSH XH
	PUSH XL

	mov tempregister, nmbrOfCacti

	LDI XH, HIGH(cactusMemory) 
	LDI XL, LOW(cactusMemory)

	moveNextCactus:
		CPI tempregister,0
		BREQ noCactiLeft
		DEC tempregister

		LD xpos, X
		DEC xpos			// Move cactus 1 xpos to the left
		BRNE store
			//Cactus is at the end left, must be deleted
			DEC nmbrOfCacti
			RCALL deleteFirstCactus
			RJMP moveNextCactus

		store:
			ST X, xpos

			INC XL
			INC XL
			RJMP moveNextCactus

	noCactiLeft:
		POP XL
		POP XH
		POP tempregister
		POP xpos
		RET

deleteFirstCactus:
// Deletes the first cactus of cactusMemory and shifts the remaining cacti
// Changed registers: /
// Called Functions: /

	PUSH xpos
	PUSH tempregister
	PUSH nmbrOfCacti
	PUSH XH
	PUSH XL

	mov tempregister, nmbrOfCacti

	LDI XH, HIGH(cactusMemory) 
	LDI XL, LOW(cactusMemory)

	LSL tempregister

	stillDeleting:
		BREQ deletingDone
		ADIW XL,2
		LD xpos,X
		DEC XL
		DEC XL
		ST X+,xpos
		DEC tempregister
		RJMP stillDeleting


	deletingDone:
	POP XL
	POP XH
	POP nmbrOfCacti
	POP tempregister
	POP xpos
	
	RET

newCactusOrNot:
// Will decide if a new cactus will be added or not, for this purpose it uses a PRNG
// Changed registers: nmbrOfCacti
// Called functions: addCactus, random
	PUSH tempregister
	PUSH maxNmbrOfCacti
	PUSH XH
	PUSH XL
	PUSH xpos

	LDI XH, HIGH(cactusMemory)
	LDI XL, LOW(cactusMemory)

	CP maxNmbrOfCacti,nmbrOfCacti
	BREQ noNewCactus				; No new cactus if max nmbr of cacti for this level is met

	MOV tempregister, nmbrOfCacti
	CPI tempregister,0
	BREQ noCheckNeeded				; If no Cactus on the screen, of course a new one is allowed.
	DEC tempregister
	LSL tempregister
	ADD XL , tempregister
	LD xpos, X
	CPI xpos,32						
	BRSH noNewCactus				; To make sure that there is enough place between 2 cacti

	CPI xpos,7						; To make sure that at the moment of insane/normal mode transition there is enough place between 2 cacti
	BRLO noNewCactus

	noCheckNeeded:
	RCALL random					; A random number is generated in randomNumber
	
	MOV tempregister,randomNumber

	CPI tempregister,3
	BRSH noNewCactus // A 3/32 chance of new cactus

	RCALL addCactus

	noNewCactus:
	POP xpos
	POP XL
	POP XH
	POP maxNmbrOfCacti
	POP tempregister
	RET

initDino:
// Initiates a new dino in dinoMemory
// Changed registers: /
	PUSH xpos
	PUSH ypos
	PUSH XH
	PUSH XL

	LDI XH, HIGH(dinoMemory)			// Point to start of dinoMemory
	LDI XL, LOW(dinoMemory)

		LDI xpos, 4							// xpos of dino
		ST X+, xpos
		LDI ypos, 8
		ST X+, ypos
		RJMP initDinoRet

	initDinoRet:
	POP XL
	POP XH
	POP ypos
	POP xpos
	RET

inverseDinoPos:
// Initiates the dino coordinates at the inverse position as it is actually. Will overwrite the current coordinates
// Changed registers: /
// Functions called: /
	PUSH XH
	PUSH XL
	PUSH tempregister
	PUSH xpos
	
	LDI XH, HIGH(dinoMemory)			// Point to start of dinoMemory
	LDI XL, LOW(dinoMemory)
	LD xpos,X
	LDI tempregister,39
	SUB tempregister,xpos
	MOV xpos,tempregister
	ST X, xpos

	POP xpos
	POP tempregister
	POP XL
	POP XH
	RET

updateScore:
// When called this function will increment the score by one.
// Changed registers: Z-pointer
// Functions called: /
	PUSH tempregister

	LDI tempregister,0b00001111
	AND tempregister,ZL
	CPI tempregister,9
	BRSH overflowZLL
		INC ZL
		RJMP updateScoreRet
	overflowZLL:
		LDI tempregister,0b11110000
		AND tempregister,ZL
		CPI tempregister,0b10010000 ;0b1001 0000 = 0x90
		BRSH overflowZL
			MOV ZL,tempregister
			LDI tempregister,0b00010000
			ADD ZL,tempregister
			RJMP updateScoreRet
		overflowZL:
			CLR ZL
			LDI tempregister,0b00001111
			AND tempregister,ZH
			CPI tempregister,9
			BRSH overflowZHL
				INC ZH
				RJMP updateScoreRet
			overflowZHL:
				LDI tempregister,0b11110000
				AND tempregister,ZH
				CPI tempregister,0b10010000 ; 0b1001 0000 = 0x90
				BRSH overflowZH
					MOV ZH,tempregister
					LDI tempregister,0b00010000
					ADD ZH,tempregister
					RJMP updateScoreRet
				overflowZH:
					LDI ZH,0b10011001
					LDI ZL,0b10011001
	updateScoreRet:
	POP tempregister
	RET