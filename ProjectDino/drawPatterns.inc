;
; The dinosaur game ('The dino says Graaah!')
;
; Sensors and microsystem electronics
; Year: 2017-2018
; Authors : Remco Royen & Johan Jacobs
;
; drawPatterns.inc

drawGameOver:
// Draws Game Over on the screen
// Changed registers: /
// Called functions: drawPixel
	PUSH xpos
	PUSH ypos
	; Row 1
	LDI xpos,4
	LDI ypos,1
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel

	; Row 2
	LDI xpos,4
	INC ypos
		; Letter G
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	INC xpos
		; Letter A
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter M
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	; Letter O
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter V
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	; Letter R
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel

	; Row 3
	LDI xpos,4
	INC ypos
		; Letter G
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	INC xpos
		; Letter A
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter M
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	; Letter O
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter V
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	; Letter R
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel

	; Row 4
	LDI xpos,4
	INC ypos
		; Letter G
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
		; Letter A
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter M
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	; Letter O
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter V
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter R
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos

	; Row 4
	LDI xpos,4
	INC ypos
		; Letter G
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
		; Letter A
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter M
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	; Letter O
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter V
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	; Letter R
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos

	; Row 5
	LDI xpos,4
	INC ypos
		; Letter G
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
		; Letter A
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter M
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	; Letter O
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter V
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	; Letter R
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel

	; Row 6
	LDI xpos,4
	INC ypos
		; Letter G
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
		; Letter A
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter M
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	INC xpos
	INC xpos
	; Letter O
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter V
	INC xpos
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	; Letter E
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	; Letter R
	INC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel

	POP ypos
	POP xpos
	RET

drawZero:
// Draws a 0 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	DEC xpos
	RET

drawOne:
// Draws a 1 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC xpos
	INC ypos
	RCALL drawPixel
	INC xpos
	INC xpos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	SBIW xpos,2
	DEC ypos
	DEC ypos
	DEC ypos
	DEC ypos
	RET

drawTwo:
// Draws a 2 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
	RCALL drawPixel
	INC ypos
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
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	DEC ypos
	DEC ypos
	DEC ypos
	DEC ypos
	DEC xpos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	RET

drawThree:
// Draws a 3 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	INC ypos
	INC ypos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	INC ypos
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC ypos
	DEC ypos
	DEC ypos
	DEC ypos
	RET

drawFour:
// Draws a 4 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
	RCALL drawPixel
	DEC xpos
	DEC xpos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	INC ypos
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	SBIW xpos,2
	DEC ypos
	DEC ypos
	DEC ypos
	DEC ypos
	RET

drawFive:
// Draws a 5 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
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
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC ypos
	DEC ypos
	DEC ypos
	DEC ypos
	RET

drawSix:
// Draws a 6 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
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
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	DEC ypos
	DEC ypos
	DEC ypos
	RET	

drawSeven:
// Draws a 7 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	INC xpos
	INC xpos
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	INC xpos
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	SBIW xpos,2
	DEC ypos
	DEC ypos
	DEC ypos
	DEC ypos
	RET

drawEight:
// Draws a 8 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
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
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	INC ypos
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	DEC ypos
	DEC ypos
	DEC ypos
	RET	
	
drawNine:
// Draws a 9 with top right corner given by xpos, ypos
// Changed registers: /
// Called functions: drawPixel
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
	RCALL drawPixel
	INC xpos
	RCALL drawPixel
	DEC ypos
	RCALL drawPixel
	INC ypos
	INC ypos
	RCALL drawPixel
	INC ypos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC xpos
	RCALL drawPixel
	DEC ypos
	DEC ypos
	DEC ypos
	DEC ypos
	RET