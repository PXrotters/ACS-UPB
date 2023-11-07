section .data

section .text
    global bonus

bonus:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; board

    ;; DO NOT MODIFY
    ;; FREESTYLE STARTS HERE
    ;;Vom avea mai multe cazuri de tratat (colturi, marginile si interior)
    ;;Verificam daca suntem pe linia de sus/jos
    sus_jos:
    cmp eax, 7 ; Linia de sus
    je linie_sus
    cmp eax, 0 ; Linia de jos
    je linie_jos
    jmp stanga_dreapta ; Mergem si tratam marginile stanga dreapta

    ;;Verificam daca suntem in colturile liniei de sus sau pe margine
    linie_sus:
    cmp ebx, 7 ; Coltul dreapta sus (7,7)
    je dreapta_sus
    cmp ebx, 0 ; Coltul stanga sus (7,0)
    je stanga_sus
    jmp margine_sus ; Mergem si tratam doar marginile

    ;;Cazul in care ne aflam in coltul din dreapta sus (7,7)
    dreapta_sus:
    mov byte[ecx + 2], 1 ; Punem 1 pe prima pozitie de pe linia 6 din matrice (6,0)
    dec ebx ; Vom efectua 6 shiftari la stanga pentru a ajunge pe pozitia (6,6)
    mov edx, ebx ; Retinem numarul de shiftari pe care urmeaza sa le efectuam
    jmp shifting_sus
    jmp final

    ;;Cazul in care ne aflam in coltul din stanga sus (7,0)
    stanga_sus:
    mov byte[ecx + 2], 1 ; Punem 1 pe prima pozitie de pe linia 6 din matrice (6,0)
    inc ebx ; Vom efectua o shiftare la stanga pentru a ajunge pe pozitia (6,6)
    mov edx, ebx ; Retinem numarul de shiftari pe care urmeaza sa le efectuam
    jmp shifting_sus
    jmp final

    ;;Cazul in care ne aflam pe marginea de sus a matricii (7,X)
    margine_sus:
    mov byte[ecx + 2], 1 ; Punem 1 pe prima pozitie de pe linia 6 din matrice (6,0)
    shl byte[ecx + 2], 2 ; Shiftam de 2 ori la stanga
    or byte[ecx + 2], 1 ; Punem 1 pe prima pozitie de pe linia 6 din matrice (6,0)
    ;;Astfel vom avea pe linia 6 : 1 0 1 pe care le putem shifta de ebx - 1 ori
    dec ebx
    mov edx, ebx ; Retinem numarul de shiftari pe care urmeaza sa le efectuam
    jmp shifting_sus
    jmp final

    ;;Verificam daca suntem in colturile liniei de jos sau pe margine
    linie_jos:
    cmp ebx, 7 ; Coltul dreapta jos (0,7)
    je dreapta_jos
    cmp ebx, 0 ; Coltul stanga jos (0,0)
    je stanga_jos
    jmp margine_jos
    jmp final

    ;;Cazul in care ne aflam in coltul din dreapta jos (0,7)
    dreapta_jos:
    mov byte[ecx + 5], 1 ; Punem 1 pe prima pozitie de pe linia 1 din matrice (1,0)
    dec ebx ; Vom efectua 6 shiftari la stanga pentru a ajunge pe pozitia (1,6)
    mov edx, ebx ; Retinem numarul de shiftari pe care urmeaza sa le efectuam
    jmp shifting_jos
    jmp final

    ;;Cazul in care ne aflam in coltul din stanga jos (0,0)
    stanga_jos:
    mov byte[ecx + 5], 1 ; Punem 1 pe prima pozitie de pe linia 1 din matrice (1,0)
    inc ebx ; Vom efectua o shiftare la stanga pentru a ajunge pe pozitia (1,1)
    mov edx, ebx ; Retinem numarul de shiftari pe care urmeaza sa le efectuam
    jmp shifting_jos
    jmp final

    ;;Cazul in care ne aflam pe marginea de jos a matricii (0,X)
    margine_jos:
    mov byte[ecx + 5], 1 ; Punem 1 pe prima pozitie de pe linia 1 din matrice (1,0)
    shl byte[ecx + 5], 2 ; Shiftam de 2 ori la stanga
    or byte[ecx + 5], 1 ; Punem 1 pe prima pozitie de pe linia 1 din matrice (1,0)
    dec ebx
    mov edx, ebx ; Retinem numarul de shiftari pe care urmeaza sa le efectuam
    jmp shifting_jos
    jmp final
    
    ;;Loop construit special pentru cazul in care ne aflam pe linia de sus (7,X)
    shifting_sus:
    ;;Verificam sa vedem daca nu cumva suntem deja pe pozitia dorita
    cmp ebx, 0 ; Daca ebx = 0 nu avem nevoie de shiftari suplimentare
    je final
    shl byte[ecx + 2], 1 ; Shitam la stanga
    dec edx ; Reducem numarul de shiftari pe care trebuie sa il mai facem
    cmp edx, 0 ; Verificam sa vedem daca am terminat numarul de shiftari necesare
    jle final
    jmp shifting_sus

    ;;Loop construit special pentru cazul in care ne aflam pe linia de jos (0,X)
    shifting_jos:
    ;;Verificam sa vedem daca nu cumva suntem deja pe pozitia dorit
    cmp ebx, 0 ; Daca ebx = 0 nu avem nevoie de shiftari suplimentare
    je final
    shl byte[ecx + 5], 1 ; Shitam la stanga
    dec edx ; Reducem numarul de shiftari pe care trebuie sa il mai facem
    cmp edx, 0 ; Verificam sa vedem daca am terminat numarul de shiftari necesare
    jle final
    jmp shifting_jos

    ;;Verificam daca suntem pe linia de stanga/dreapta
    stanga_dreapta:
    cmp ebx, 0 ; Marginea/linia din stanga matricii
    je margine_stanga
    cmp ebx, 7 ; Marginea/linia din dreapta matricii
    je margine_dreapta
    jmp final

    ;;Cazul in care ne aflam pe marginea din stanga matricii (X,0)
    margine_stanga:
    mov edx, eax ; Retinem linia pe care ne alfam initial
    inc edx ; Retinem linia de sus
    ;; Verificam sa vedem daca linia de sus se afla in partea superioara a matricii
    cmp edx, 4
    jge margine_superioara
    ;; Verificam sa vedem daca linia de sus se afla in partea inferioara a matricii
    cmp edx, 4
    jl margine_inferioara

    margine_superioara:
    ;;Pentru partea superioara a matricii putem scadea din indexul linii curente 4
    sub edx, 4
    mov ecx,[ebp + 16] ; board
    add ecx, edx ; Mergem pe linia curenta
    mov byte[ecx], 1 ; Punem 1 pe prima pozitie de pe linia curenta
    shl byte[ecx], 1 ; Shiftam la stanga
    add edx, 2 ; Mergem pe linia de jos fata de cea initiala
    ;; Verificam sa vedem daca linia de jos se afla in partea inferioara a matricii
    cmp edx, 4
    jl margine_inferioara
    ;;Altfel repetam procedeul anterior
    sub edx, 4
    mov ecx, [ebp + 16] ; board
    add ecx, edx ; Mergem pe linia curenta
    mov byte[ecx], 1 ; Punem 1 pe prima pozitie de pe linia curenta
    shl byte[ecx], 1 ; Shiftam la stanga
    jmp final

    margine_inferioara:
    ;;Pentru partea superioara a matricii putem aduna la indexul linii curente 4
    ;;Noi in continuare ne afla pe linia de sus fata de cea initiala
    mov esi, 4
    mov ecx, [ebp + 16] ; board
    add esi, edx ; Adunam 4 la linia curenta si salvam rezultatul in esi
    add ecx, esi ; Mergem pe linia curenta
    mov byte[ecx], 1 ; Punem 1 pe prima pozitie de pe linia curenta
    shl byte[ecx], 1 ; Shiftam la stanga
    sub edx, 2 ; Mergem pe linia de jos celei initiale
    ;; Verificam sa vedem daca linia de jos se afla in partea inferioara a matricii
    cmp edx, 4
    jg margine_superioara
    ;;Altfel repetam procedeul anterior
    mov esi, 4
    mov ecx, [ebp + 16] ; board
    add esi, edx ; Adunam 4 la linia curenta si salvam rezultatul in esi
    add ecx, esi ; Mergem pe linia curenta
    mov byte[ecx], 1 ; Punem 1 pe prima pozitie de pe linia curenta
    shl byte[ecx], 1 ; Shiftam la stanga
    jmp final

    ;;Cazul in care ne aflam pe marginea din dreapta matricii (X,7)
    margine_dreapta:
    mov edx, eax ; Retinem linia pe care ne alfam initial
    inc edx ; Retinem linia de sus
    ;; Verificam sa vedem daca linia de sus se afla in partea superioara a matricii
    cmp edx, 4
    jge margine_superioara_2
    ;; Verificam sa vedem daca linia de sus se afla in partea inferioara a matricii
    cmp edx, 4
    jl margine_inferioara_2

    margine_superioara_2:
    sub edx, 4
    mov ecx, [ebp + 16] ; board
    add ecx, edx ; Mergem pe linia curenta
    mov byte[ecx], 1 ; Punem 1 pe prima pozitie de pe linia curenta
    shl byte[ecx], 6 ; Shiftam la stanga de 6 ori
    add edx, 2 ; Mergem pe linia de jos celei initiale
    ;; Verificam sa vedem daca linia de jos se afla in partea inferioara a matricii
    cmp edx, 4
    jl margine_inferioara_2
    ;;Altfel repetam procedeul anterior
    sub edx, 4
    mov ecx, [ebp + 16] ; board
    add ecx, edx ; Mergem pe linia curenta
    mov byte[ecx], 1 ; Punem 1 pe prima pozitie de pe linia curenta
    shl byte[ecx], 6 ; Shiftam la stanga de 6 ori
    jmp final

    margine_inferioara_2:
    mov esi, 4
    mov ecx, [ebp + 16] ; board
    add esi, edx ; Adunam 4 la linia curenta si salvam rezultatul in esi
    add ecx, esi ; Mergem pe linia curenta
    mov byte[ecx], 1 ; Punem 1 pe prima pozitie de pe linia curenta
    shl byte[ecx], 6 ; Shiftam la stanga de 6 ori
    sub edx, 2
    cmp edx, 4
    jg margine_superioara_2
    mov esi, 4
    mov ecx, [ebp + 16] ; board
    add esi, edx ; Adunam 4 la linia curenta si salvam rezultatul in esi
    add ecx, esi ; Mergem pe linia curenta
    mov byte[ecx], 1 ; Punem 1 pe prima pozitie de pe linia curenta
    shl byte[ecx], 6 ; Shiftam la stanga de 6 ori
    jmp final

    final:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY