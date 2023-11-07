struc proc
    .pid: resw 1
    .prio: resb 1
    .time: resw 1
endstruc

section .text
    global sort_procs

sort_procs:
    ;; DO NOT MODIFY
    enter 0,0
    pusha

    mov edx, [ebp + 8]      ; processes
    mov eax, [ebp + 12]     ; length
    ;; DO NOT MODIFY

    ;; Your code starts here
    mov edi, eax ; Retinem numarul de procese
    mov esi, edx ; Retinem vect
    mov ecx, edi ; Retinem numarul de procese

    ;;Prioritate 1
    prioritati:
    cmp edi, 1
    je reluare_bucla ; Daca am ajuns la ultimul element reluam procesul
    mov al, [esi + proc.prio] ; Retinem prioritatea el din stanga
    add esi, 5 ; Trecem la urmatorul element
    mov bl, [esi + proc.prio] ; Retinem prioritatea el din dreapta
    cmp al, bl
    je timp ; Daca sunt egale trecem sa verificam timpul
    cmp al, bl
    jg swap ; Daca primul este mai mare ordonam
    dec edi
    jmp prioritati ; Altfel daca sunt deja ordonate trecem la urmatoarele 2 el

    timp:
    sub esi, 5 ; Revenim la poz anterioara
    mov eax, 0
    mov ebx, 0
    mov ax, [esi + proc.time] ; Retinem timpul el din stanga
    add esi, 5 ; Trecem la urmatorul element
    mov bx, [esi + proc.time] ; Retinem timpul el din dreapta
    cmp ax, bx
    je id ; Daca sunt egale trecem sa verificam id-ul
    cmp ax, bx
    jg swap ; Daca primul este mai mare ordonam
    dec edi
    jmp prioritati ; Altfel daca sunt deja ordonate trecem la urmatoarele 2 el

    id:
    sub esi, 5 ; Revenim la poz anterioara
    mov eax, 0
    mov ebx, 0
    mov ax, [esi + proc.pid] ; Retinem id-ul el din stanga
    add esi, 5 ; Trecem la urmatorul element
    mov bx, [esi + proc.pid] ; Retinem id-ul el din dreapta
    cmp ax, bx
    jg swap ; Daca primul este mai mare ordonam
    dec edi
    jmp prioritati ; Altfel daca sunt deja ordonate trecem la urmatoarele 2 el

    swap:
    ;;Sortarea prioritatilor
    sub esi, 5 ; Revenim la pozitia anterioara
    mov al, [esi + proc.prio] ; Retinem prioritatea el din stanga
    add esi, 5 ; Trecem la urmatorul element
    mov bl, [esi + proc.prio] ; Retinem prioritatea el din dreapta
    mov dl, bl
    ;;Realizam interschimbarea
    mov [esi + proc.prio], al
    sub esi, 5 ; Revenim la pozitia anterioara
    mov [esi + proc.prio], dl
    add esi, 5 ; Revenim la poz curenta

    ;;Sortarea timpilor
    sub esi, 5 ; Revenim la pozitia anterioara
    mov ax, [esi + proc.time] ; Retinem timpul el din stanga
    add esi, 5 ; Trecem la urmatorul element
    mov bx, [esi + proc.time] ; Retinem timpul el din dreapta
    mov dx, bx
    ;;Realizam interschimbarea
    mov  [esi + proc.time], ax
    sub esi, 5 ; Revenim la pozitia anterioara
    mov  [esi + proc.time], dx
    add esi, 5 ; Revenim la poz curenta

    ;;Sortarea id-urilor 
    sub esi, 5 ; Revenim la pozitia anterioara
    mov ax, [esi + proc.pid] ; Retinem id-ul el din stanga
    add esi, 5 ; Trecem la urmatorul element
    mov bx, [esi + proc.pid] ; Retinem id-ul el din dreapta
    mov dx, bx
    ;;Realizam interschimbarea
    mov  [esi + proc.pid], ax
    sub esi, 5 ; Revenim la pozitia anterioara
    mov  [esi + proc.pid], dx
    add esi, 5 ; Revenim la poz curenta
    dec edi
    jmp prioritati

    reluare_bucla:
    dec ecx
    cmp ecx, 0
    je final
    mov esi, [ebp + 8] ; Adresa de inceput a vect
    mov edi, [ebp + 12] ; length initial
    jmp prioritati

    final:

    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY