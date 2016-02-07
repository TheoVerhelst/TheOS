extern descriptor;

; 0x10 corresponds to a code segment, for a GDT table
; and with maximum privileges
%define CODE_SEGMENT 0x10
; 0x08 corresponds to a data segment, for a GDT table
; and with maximum privileges
%define DATA_SEGMENT 0x08

; A flush is simply reset all segment register to default values (see above)
global flushGDT
flushGDT:
    lgdt [descriptor]
    ; This instruction, by doing a far jump, set cs to 0x08
    jmp CODE_SEGMENT:continueFlush

continueFlush:
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
