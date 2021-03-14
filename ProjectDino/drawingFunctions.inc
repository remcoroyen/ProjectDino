;
; The dinosaur game ('The dino says Graaah!')
;
; Sensors and microsystem electronics
; Year: 2017-2018
; Authors : Remco Royen & Johan Jacobs
;
; drawingFunctions.inc

  flushMemory:
// Flushes the buffer to the screen
// Changed parameters: illuminatedRow, registerBitCounter, memoryByteAddress
// Called functions: waitingLoop

	PUSH XH
	PUSH XL

	CLR illuminatedRow
	LDI XH, HIGH(bufferStartAddress)
	LDI XL, LOW(bufferStartAddress)
	SBIW XL,10

	nextRow:
		ADIW XL,20
		INC illuminatedRow
		CPI illuminatedRow,8
		BRNE notmax

	
	turnOnLastRow:
		LDI counter,88
		loopLastRow:
			CBI PORTB,3
			SBI PORTB,5
			CBI PORTB,5
			DEC counter
			BRNE loopLastRow

		SBI PORTB,4
		RCALL waitingLoop
		CBI PORTB,4
		RCALL waitingLoop

		POP XL
		POP XH
		RET

		notmax:

		LDI counter,80
		columnbits:
			LD memoryByteRegister,-X ; -X = predec while X+ = postdec
			LDI registerBitCounter,8

			bitsOfRegister:
					SBRS flags,1
					RJMP normalMode
				extremeMode:
					SBRS memoryByteRegister,7
					RJMP pixelOn
					RJMP pixelOff

				normalMode:
					SBRC memoryByteRegister,7
					RJMP pixelOn

				; Pixel off
				pixelOff:
					CBI PORTB,3
					RJMP administration
					
				; Pixel on
				pixelOn:
					SBI PORTB,3
				
				administration:	
					SBI PORTB,5
					CBI PORTB,5
					DEC counter
					BREQ rows
					DEC registerBitCounter
					BREQ columnbits
					LSL memoryByteRegister
					RJMP bitsOfRegister	

			rows:
				LDI counter,8
			rowbits:

				CP counter, illuminatedRow
				BREQ rowSet
					CBI PORTB,3
					RJMP nextStep
	
				rowSet:
					SBI PORTB,3

				nextStep:
					SBI PORTB,5
					CBI PORTB,5
					DEC counter
					BREQ latching
					RJMP rowbits

		latching:
			SBI PORTB,4
			RCALL waitingLoop
			CBI PORTB,4
			RCALL waitingLoop
			RJMP nextRow

RET

 clearBuffer:
// Clears the buffer in the memory which will be later on flushed to screen by 'flushMemory'
// Changed registers: /
// Called functions: /

	PUSH XH
	PUSH XL
	PUSH tempRegister
	PUSH counter

	LDI XH,0x01
	CLR XL

	LDI counter,70
	CLR tempRegister
	clearingLoop:
		ST X+,tempRegister
		DEC counter
		BRNE clearingLoop

	POP counter
	POP tempRegister
	POP XL
	POP XH
RET

drawPixel:
// Draws the pixel indicated by the values of registers xpos and ypos. The first row is row 0 and the first column is column 0
// Changed parameters: flags, xpos -> xpos+1, ypos -> ypos+1
// Called functions: /

	PUSH xpos
	PUSH ypos

	PUSH counter
	PUSH tempregister

	PUSH XH
	PUSH XL

	LDI XH, HIGH(bufferStartAddress)
	LDI XL, LOW(bufferStartAddress)

	CPI ypos,7
	BRLO UpperPartScreen

		SUBI ypos,7
		ADIW xpos, 40

	UpperPartScreen:

		LDI tempRegister,10
		MUL ypos,tempRegister
		ADD XL,mulLSB

		MOV tempRegister,xpos
		LSR tempregister
		LSR tempregister
		LSR tempregister
		ADD XL,tempregister
		
		ANDI xpos, 0b00000111
		LDI counter,0
		LDI tempregister,1
		bitContent:
			CP xpos,counter
			BREQ bitFound
			LSL tempregister
			INC counter
			RJMP bitContent
		
		bitfound:
		
		LD xpos, X ; The old byte content is stored in xpos

		; Collision detect
		MOV counter,xpos ; Counter is used as a temp register
		AND counter,tempregister
		CPI counter,0
		BREQ noCollision
			SBR flags,1

		noCollision:
		; Draw updated field
		OR tempregister,xpos
		ST X+,tempregister	
	
	POP XL
	POP XH

	POP tempregister
	POP counter

	POP ypos
	POP xpos

RET

drawScore:
// Receives the top right coordinates by xpos and ypos and draws the appropriate score
// Changed registers: /
// Called functions: draw0,1,2,3,4,5,6,7,8,9
	PUSH ZL
	PUSH ZH
	PUSH tempregister
	PUSH counter
	PUSH xpos
	PUSH ypos

	CPI gameState,0
	BRNE gameOverModus
		LDI ypos,1
		LDI xpos,38

		SBRC flags,4
		LDI xpos,15
		RJMP drawScoreStart
	gameOverModus:
		LDI xpos, 27
		LDI ypos, 9

	drawScoreStart:
	LDI counter,5

	nextNumber:
	DEC counter
	BREQ drawScoreRet

	LDI tempregister,0b00001111
	AND tempregister,ZL
		
	CPI tempregister,0
	BRNE maybe1
		RCALL drawZero
		RJMP numberReady
	
	maybe1:
	CPI tempregister,1
	BRNE maybe2
		RCALL drawOne
		RJMP numberReady
	maybe2:

	CPI tempregister,2
	BRNE maybe3
		RCALL drawTwo
		RJMP numberReady

	maybe3:
	CPI tempregister,3
	BRNE maybe4
		RCALL drawThree
		RJMP numberReady

	maybe4:
	CPI tempregister,4
	BRNE maybe5
		RCALL drawFour
		RJMP numberReady

	maybe5:

	CPI tempregister,5
	BRNE maybe6
		RCALL drawFive
		RJMP numberReady

	maybe6:

	CPI tempregister,6
	BRNE maybe7
		RCALL drawSix
		RJMP numberReady

	maybe7:

	CPI tempregister,7
	BRNE maybe8
		RCALL drawSeven
		RJMP numberReady

	maybe8:

	CPI tempregister,8
	BRNE maybe9
		RCALL drawEight		
		RJMP numberReady

	maybe9:
		RCALL drawNine
		
	numberReady:

	DEC xpos
	DEC xpos

	LDI tempregister,5
	shiftingToNext:
	DEC tempregister
	BREQ nextNumber
		LSR ZH
		ROR ZL
		RJMP shiftingToNext

	drawScoreRet:
	POP ypos
	POP xpos
	POP counter
	POP tempregister
	POP ZH
	POP ZL
	RET

drawCactus:
// Draws the cacti in the buffer, ready to flush
// Changed parameters: /
// Called functions: drawPixel
	PUSH xpos
	PUSH ypos
	PUSH nmbrOfCacti
	PUSH counter ; will be used as normal variable
	PUSH tempregister
	PUSH XH
	PUSH XL

	MOV tempregister,nmbrOfCacti

	// Assume that x and y postions of the first cactus to draw are saved in respectively the first byte at cactusMemory and the 2nd byte
	LDI XH, HIGH(cactusMemory) 
	LDI XL, LOW(cactusMemory)

	drawNextCactus:
		CPI tempregister,0
		BREQ noCactusLeft 
		DEC tempregister

		LD xpos, X+
		LD ypos, X+	

		SBRS flags,4
		RJMP actualDrawing
		LDI counter,39
		SUB counter,xpos
		MOV xpos, counter

		actualDrawing:
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		INC xpos
		RCALL drawPixel
		DEC xpos
		DEC xpos
		RCALL drawPixel
		INC xpos
		INC ypos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel

		RJMP drawNextCactus


	noCactusLeft:	
		POP XL
		POP XH
		POP tempregister
		POP counter
		POP nmbrOfCacti
		POP ypos
		POP xpos
		RET

drawDino:
// Draws the dino in the buffer, ready to flush
// Changed registers: /
// Called fucntions: drawPixel
	PUSH xpos
	PUSH ypos

	PUSH XH
	PUSH XL

	LDI XH, HIGH(dinoMemory)	// Assume that x and y postions of the first cactus to draw are saved in respectively the first byte at cactusMemory and the 2nd byte
	LDI XL, LOW(dinoMemory)
	LD xpos, X+
	LD ypos, X

	SBRC flags,4
	RJMP insaneDrawDino

		RCALL drawPixel
		DEC xpos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		INC xpos
		RCALL drawPixel
		DEC xpos
		INC ypos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		DEC ypos
		DEC ypos
		DEC xpos
		RCALL drawPixel
		DEC ypos
		RCALL drawPixel
		DEC xpos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		RJMP drawDinoRet

	insaneDrawDino:

		RCALL drawPixel
		INC xpos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		DEC xpos
		RCALL drawPixel
		INC xpos
		INC xpos
		RCALL drawPixel
		INC xpos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		DEC xpos
		RCALL drawPixel
		DEC xpos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		INC ypos
		RCALL drawPixel
		INC xpos
		INC xpos
		RCALL drawPixel
		DEC ypos
		RCALL drawPixel
	
	drawDinoRet:
	POP XL
	POP XH
	POP ypos
	POP xpos
	RET