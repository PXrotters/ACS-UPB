%include "../include/io.mac"

section .text
    global simple
    extern printf

simple:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     ecx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; plain
    mov     edi, [ebp + 16] ; enc_string
    mov     edx, [ebp + 20] ; step

    ;; DO NOT MODIFY
   
    ;; Your code starts here

    ;; Your code starts here
    mov eax, 0  ; index - parcurgere text

    loop_char:
    cmp eax, ecx ; compara index cu lungime text
    jge finish ; daca indexul este mai mare sau egal decat dimensiune iesim din bucla
    mov bl, byte [esi + eax] ; retinem pozitia in bl
    sub bl, 'A' ; convertim poztia retinuta anterior in cifra(poz in alfabet)
    add bl, dl ; efectuam adunarea(noua poz din alfabet)
    cmp bl, 25 ; comparam sa vedem daca bl < 26
    jle  convert ; in caz afirmativ sarim la eticheta convert
    sub bl, 26 ; in caz contrar se scade din nr 26 care vine valoarea noii litere dupa o parcurgere a alfabetului

    convert:
    add bl, 'A' ; convertim pozitia inapoi in litera
    mov byte [edi + eax], bl ; copiem noua litera in poz respectiva din enc_string
    inc eax
    jmp loop_char ; reluam bucla

    finish:
    ;; Your code ends here
    
    ;; DO NOT MODIFY

    popa
    leave
    ret
    
    ;; DO NOT MODIFY
