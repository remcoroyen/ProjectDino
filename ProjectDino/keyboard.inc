;
; The dinosaur game ('The dino says Graaah!')
;
; Sensors and microsystem electronics
; Year: 2017-2018
; Authors : Remco Royen & Johan Jacobs
;
; keyboard.inc

 checkKeyboard:
 // Checks if button of keyboard is pressed and reacts
 // Changed registers: flags, dinoJumping, gameState
 // Functions called: initGame, seedMaker
	PUSH R16
	PUSH R17
	PUSH R18
	; Configure rows as inputs
	CBI DDRD,4
	SBI PORTD,4
	CBI DDRD,5
	SBI PORTD,5
	CBI DDRD,6
	SBI PORTD,6
	CBI DDRD,7
	SBI PORTD,7
	; Configure columns as outputs: outputs cannot have a pull-up resistor
	SBI DDRD,0
	SBI DDRD,1
	SBI DDRD,2
	SBI DDRD,3

	; Two step method
	; Set columns low (outputs): write zeros to outputs and check if we read something from input
	; CBI PORTD,4 --> this would turn off the pull up resistor at the input, which doesn't make sense
	CBI PORTD,0
	CBI PORTD,1
	CBI PORTD,2
	CBI PORTD,3
	; Read from rows (inputs)
	LDI R16,1			; Row counter

	SBIS PIND, 4
	RJMP readColumns
	LSL R16
	SBIS PIND, 5
	RJMP readColumns
	LSL R16
	SBIS PIND, 6
	RJMP readColumns
	LSL R16
	SBIS PIND, 7
	RJMP readColumns
	RJMP nothingPressed					; If nothing is pressed, return to rest of program



	readColumns:
	; Configure columns as inputs
	CBI DDRD,0
	SBI PORTD,0
	CBI DDRD,1
	SBI PORTD,1
	CBI DDRD,2
	SBI PORTD,2
	CBI DDRD,3
	SBI PORTD,3
	; Configure rows as outputs
	SBI DDRD,4
	SBI DDRD,5
	SBI DDRD,6
	SBI DDRD,7


	; Set rows low (outputs): write zeros to outputs and check if we read something from input
	CBI PORTD,4
	CBI PORTD,5
	CBI PORTD,6
	CBI PORTD,7

	; Read from columns (inputs)
	LDI R17,16			; Column counter

	SBIS PIND, 0
	RJMP evaluate
	LSL R17
	SBIS PIND, 1
	RJMP evaluate
	LSL R17
	SBIS PIND, 2
	RJMP evaluate
	LSL R17
	SBIS PIND, 3
	RJMP evaluate
	RJMP nothingPressed			; All columns are high so no button was pressed

	evaluate:
	ADD R16, R17

	LDI R18, 0b10001000				; Evaluate button 7: 1000 1000
	CP R16, R18
	BREQ button7

	LDI R18, 0b10000001				; Evaluate button A: 1000 0001
	CP R16, R18
	BREQ buttonA

	RJMP checkKeyboardRet			; No useful key was pressed

	button7:
		SBRC flags,3
		RJMP checkKeyboardRet
		CPI dinoJumping,0
		BRNE checkKeyboardRet
		SBR flags,0b00001000
		LDI dinoJumping,4
		RJMP checkKeyboardRet

	buttonA:
		SBRC flags,3
		RJMP checkKeyboardRet
		SBR flags,0b00001000
		RCALL seedMaker
		RCALL initGame
		CLR gameState
		RJMP checkKeyboardRet

	nothingPressed:
		CBR flags,0b00001000

	checkKeyboardRet:
		POP R18
		POP R17
		POP R16
		RET