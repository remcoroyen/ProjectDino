;
; The dinosaur game ('The dino says Graaah!')
;
; Sensors and microsystem electronics
; Year: 2017-2018
; Authors : Remco Royen & Johan Jacobs
;
; macros.inc

 .MACRO MOD			; mod(@0,@1) -> mod(7,4) = 3
	PUSH @0			; Save current value
	subtract:
		SUB @0, @1
		BRSH subtract
	ADD @0,@1
	MOV tempRegister,@0
	POP @0
.ENDMACRO