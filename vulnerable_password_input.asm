.model tiny
.186
.code
org 100h

Start:      mov ah, 09h                     
            mov dx, offset Frame          
            int 21h                         

            mov ah, 0ah                    
            mov dx, offset InputLine       
            int 21h                        

            mov si, offset InputLine       
            add si, 02h                        
            mov ah, 09h
            mov cx, 08h

            mov al, 20h
            cmp al, ds:[si]
            je Right

            mov di, offset Key              ;              |----------------------------------------------------------------|      
            repe cmpsb                      ;              | First vulnerability! JE is written erroneously instead of JNE! |
            je Right                        ;------------->|               Empty password will be right!                    |
                                            :              |----------------------------------------------------------------|
Invalid:    mov dx, offset InvalidKey
            int 21h
            jmp Exit

Right:      mov dx, offset RightKey
            int 21h

Exit:       mov     ax, 4c00h
            int     21h


;------------------------------------------------
Frame:      db '.-------------------------------------------.', 0ah, 
            db '. This action requires administrator rights .', 0ah,
            db '.-------------------------------------------.', 0ah, 0ah, 
            db 'Enter password:', 0ah, '$'

InvalidKey: db 0ah, 0ah, 
            db '.-------------------------------------------.', 0ah, 
            db '. Access denied                             .', 0ah, 
            db '.-------------------------------------------.', 0ah, '$'

RightKey:   db 0ah, 0ah, 
            db '.-------------------------------------------.', 0ah, 
            db '. Access allowed                            .', 0ah, 
            db '.-------------------------------------------.', 0ah, 0ah, 
            db 'Umiraet staryj korol. I reshil on razdelit', 0ah, 
            db 'svoe bogatstvo mezhdu tremya synovyami.', 0ah,
            db '- Afigenno! - skazal chetvertyj syn.$'


InputLine:  db '$$$$$$$$$$'                 ; ------------> |-----------------------------------------------------------------------------|
Key: db 'pylesos', 0dh                      ;               | Second vulnerability! Buffer overflow is not controlled! Access can be      |
                                            ;               | obtained by entering a 16-bytes password, consisting of two identical words |
                                            ;               | For example: '1234567812345678' will be right key                           |
                                            ;               |-----------------------------------------------------------------------------|
;------------------------------------------------


end Start
