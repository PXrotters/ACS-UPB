%include "../include/io.mac"

struc avg
    .quo: resw 1
    .remain: resw 1
endstruc    

struc proc
    .pid: resw 1
    .prio: resb 1
    .time: resw 1
endstruc

    ;; Hint: you can use these global arrays
section .data
    prio_result dd 0, 0, 0, 0, 0
    time_result dd 0, 0, 0, 0, 0

section .text
    global run_procs

run_procs:
    ;; DO NOT MODIFY

    push ebp
    mov ebp, esp
    pusha

    xor ecx, ecx

clean_results:
    mov dword [time_result + 4 * ecx], dword 0
    mov dword [prio_result + 4 * ecx],  0

    inc ecx
    cmp ecx, 5
    jne clean_results

    mov ecx, [ebp + 8]      ; processes
    mov ebx, [ebp + 12]     ; length
    mov eax, [ebp + 16]     ; proc_avg
    ;; DO NOT MODIFY
   
    ;; Your code starts here
    ;;Calculam sumele pentru fiecare prioritate
    ;;Prioritate 1
    mov edi, ebx ; Retinem numarul de procese(index)
    mov al, 1
    mov ebx, 0

    sum1:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element1 ; Trecem la urmatorul element
    mov ebx, 0
    add bx, [ecx + proc.time] ; Constituim suma prioritatii curente
    add time_result[0], ebx ; Reinem suma in vect (poz este prioritatea)
    
    next_element1:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne sum1

    ;;Prioritate 2
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edi, ebx ; Retinem numarul de procese(index)
    mov al, 2

    sum2:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element2 ; Trecem la urmatorul element
    mov ebx, 0
    add bx, [ecx + proc.time] ; Constituim suma prioritatii curente
    add time_result[4], ebx ; Reinem suma in vect (poz este prioritatea)
    
    next_element2:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne sum2

    ;;Prioritate 3
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edi, ebx ; Retinem numarul de procese(index)
    mov al, 3

    sum3:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element3 ; Trecem la urmatorul element
    mov ebx, 0
    add bx, [ecx + proc.time] ; Constituim suma prioritatii curente
    add time_result[8], ebx ; Reinem suma in vect (poz este prioritatea)

    next_element3:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne sum3

    ;;Prioritate 4
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edi, ebx ; Retinem numarul de procese(index)
  
    mov al, 4

    sum4:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element4 ; Trecem la urmatorul element
    mov ebx, 0
    add bx, [ecx + proc.time] ; Constituim suma prioritatii curente
    add time_result[12], ebx ; Reinem suma in vect (poz este prioritatea)

    next_element4:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne sum4

    ;;Prioritate 5
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edi, ebx ; Retinem numarul de procese(index)
    mov al, 5

    sum5:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element5 ; Trecem la urmatorul element
    mov ebx, 0
    add bx, [ecx + proc.time] ; Constituim suma prioritatii curente
    add time_result[16], ebx ; Reinem suma in vect (poz este prioritatea)

    next_element5:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne sum5

    ;;Calculam numarul componentelor pentru fiecare prioritate
    ;;Prioritate 1
    mov edx, 0 ; Nr componente
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edi, ebx
    mov al, 1

    nr_comp1:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element_1 ; Trecem la urmatorul element
    inc edx ; Incrementam nr comp de tip prior_1
    mov prio_result[0], edx ; Retinem nr_comp in vect (poz este prioritatea)

    next_element_1:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne nr_comp1


    ;;Prioritate 2
    mov edx, 0 ; Nr componente
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edi, ebx
    mov al, 2

    nr_comp2:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element_2 ; Trecem la urmatorul element
    inc edx ; Incrementam nr comp de tip prior_1
    mov prio_result[4], edx ; Retinem nr_comp in vect (poz este prioritatea)

    next_element_2:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne nr_comp2

    ;;Prioritate 3
    mov edx, 0 ; Nr componente
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edi, ebx
    mov al, 3

    nr_comp3:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element_3 ; Trecem la urmatorul element
    inc edx ; Incrementam nr comp de tip prior_3
    mov prio_result[8], edx ; Retinem nr_comp in vect (poz este prioritatea)

    next_element_3:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne nr_comp3

    ;;Prioritate 4
    mov edx, 0 ; Nr componente
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edi, ebx
    mov al, 4

    nr_comp4:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element_4 ; Trecem la urmatorul element
    inc edx ; Incrementam nr comp de tip prior_4
    mov prio_result[12], edx ; Retinem nr_comp in vect (poz este prioritatea)

    next_element_4:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne nr_comp4

    ;;Prioritate 5
    mov edx, 0 ; Nr componente
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edi, ebx
    mov al, 5

    nr_comp5:
    mov bl, [ecx + proc.prio] ; Retinem prioritatea
    cmp bl, al ; Comparam sa vedem daca avem prioritatea corespunzatoare
    jne next_element_5 ; Trecem la urmatorul element
    inc edx ; Incrementam nr comp de tip prior_5
    mov prio_result[16], edx ; Retinem nr_comp in vect (poz este prioritatea)

    next_element_5:
    add ecx, 5 ; Trecem la urmatorul element
    dec edi ; Scadem indexul
    cmp edi, 0 ; Verificam daca am terminat
    jne nr_comp5


    ;;Calculam catul si restul
    mov ecx, 0

    loop:
    mov eax, time_result[edi] ; Retinem suma de pe fiecare poz (nr_prioritate)
    mov ebx, prio_result[edi] ; Retinem nr_comp de pe fiecare poz (nr_prioritate)
    cmp ebx, 0
    je nr_comp_0 ; Vedem daca avem cazul x/0
    mov edx, 0
    div ebx ; Efectuam impartirea
    mov ebx, 0
    mov ebx, [ebp + 16] ; Retinem poz de inceput a lui proc_avg
    mov word[ebx + ecx + avg.quo], ax ; Salvam catul
    mov word[ebx + ecx + avg.remain], dx ; Salvam retul
    jmp next_element ; Trecem la urmatorul element

    nr_comp_0:
    mov ebx, [ebp + 16]
    mov word[ebx + ecx + avg.quo], 0
    mov word[ebx + ecx + avg.remain], 0

    next_element:
    add ecx, 4 ; Trecem la poz urmatoare
    add edi, 4 ; Trecem la poz urmatoare
    cmp edi, 20 ; Verificam daca am term parucrgerea vectorilor
    jge final
    jmp loop

    final:

    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY