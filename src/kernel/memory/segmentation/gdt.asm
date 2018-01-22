; TODO I didn't manage to use the -I flag of nasm, this should be solved
%include "../../../include/kernel/memory/segmentation/segmentSelectors.asm"

; Put the whole code in the appropriate boot section
SECTION .bootText
    ; This is the GDT descriptor defined in boot/gtd.hpp
    extern gdtDescriptor;

    ; A flush is simply reset all segment register to default values
    global flushGdt
    flushGdt:
        lgdt [gdtDescriptor]
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
