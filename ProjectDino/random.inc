;
; The dinosaur game ('The dino says Graaah!')
;
; Sensors and microsystem electronics
; Year: 2017-2018
; Authors : Remco Royen & Johan Jacobs
;
; random.inc

random:
// Updates the SR's and uses their last bits to form the pseudo-randomNumber (5 bit long in this case)
// Changed registers: randomSR1,2,3,4,5 and randomNumber
// Called functions: updateSR
	PUSH tempregister
	PUSH passToFunctionRegister

	mov passToFunctionRegister, randomSR1
	RCALL updateSR
	mov randomSR1, passToFunctionRegister

	mov passToFunctionRegister, randomSR2
	RCALL updateSR
	mov randomSR2, passToFunctionRegister

	mov passToFunctionRegister, randomSR3
	RCALL updateSR
	mov randomSR3, passToFunctionRegister

	mov passToFunctionRegister, randomSR4
	RCALL updateSR
	mov randomSR4, passToFunctionRegister

	mov passToFunctionRegister, randomSR5
	RCALL updateSR
	mov randomSR5, passToFunctionRegister

	CLR tempregister
	SBRC randomSR1,0
	SBR tempregister,0b00000001
	SBRC randomSR2,0
	SBR tempregister,0b00000010
	SBRC randomSR3,0
	SBR tempregister,0b00000100
	SBRC randomSR4,0
	SBR tempregister,0b00001000
	SBRC randomSR5,0
	SBR tempregister,0b00010000

	MOV randomNumber,tempregister

	POP passToFunctionRegister
	POP tempregister
	RET

seedMaker:
// Uses the values of the timer at the time the 'start-button' is pressed to extract the initial values of the SR's
// Changed registers: randomSR1,2,3,4,5
// Called functions: /
	PUSH tempregister
	
	LDS randomSR1,TCNT1L
	LDS randomSR2,TCNT1H
	IN randomSR3,TCNT0
	LDS randomSR4,TCNT2
	LDS tempregister,TCNT1L
	ANDI tempregister,0b00001111
	MOV randomSR5,tempregister
	ANDI tempregister,0b11110000
	EOR randomSR5,tempregister
			
	POP tempregister
	RET

updateSR:
// Updates the SR's, these are 8-stage 4-LFSR's
// Changed registers: passToFunctionRegister
// Functions called: /
	PUSH tempregister
	PUSH counter		; Is used as a temporary register to make a mask

	ROR passToFunctionRegister
	MOV tempregister,passToFunctionRegister
	BRBS 0,carryHigh
		CBR tempregister,0b10000000
		LDI counter, 0b00000000			; mask
		RJMP continueUpdatingSR
	carryHigh:
		SBR tempregister,0b10000000
		LDI counter,0b00111000			; mask

	continueUpdatingSR:
	EOR tempregister,counter
	MOV passToFunctionRegister,tempregister

	POP counter
	POP tempregister
	RET