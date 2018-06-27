;   Module:     PeekPoke
;   Version:    1.01
;
;   Language:   Intel 80x86 Macro Assembler
;   Environ:    IBM-PC compatible
;
;   Purpose:    Provides functions to peek and poke values into specific
;               memory locations.
;
;   Written by: Scott Robert Ladd

.8086

IFDEF MML
    .MODEL LARGE,C
    %OUT "Large Model"
ELSE
    .MODEL SMALL,C
    %OUT "Small Model"
ENDIF

.CODE

PUBLIC Peek
PUBLIC Poke

Peek        PROC    segm:WORD, offs:WORD

            push    es
            push    si

            mov     ax,segm
            mov     es,ax

            mov     si,offs

            mov     ax, es:[si]

            pop     si
            pop     es

            ret

Peek        ENDP


Poke        PROC    segm:WORD, offs:WORD, value:WORD

            push    es
            push    di

            mov     ax,segm
            mov     es,ax

            mov     di,offs

            mov     cx,value

            mov     es:[di], cx

            pop     di
            pop     es

            ret

Poke        ENDP


END
