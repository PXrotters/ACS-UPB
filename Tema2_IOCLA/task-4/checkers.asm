
section .data

section .text
	global checkers

checkers:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table

    ;; DO NOT MODIFY
    ;; FREESTYLE STARTS HERE
    ;;Vom avea mai multe cazuri de tratat (colturi, marginile si interior)
    ;;Verificam daca suntem pe linia de sus-jos sau stanga-dreapta
    sus_jos:
    cmp eax, 7 ; Verificam daca ne aflam pe linia de sus
    je linie_sus
    cmp eax, 0 ; Verificam daca ne aflam pe linia de jos
    je linie_jos
    jmp stanga_dreapta

    ;;Verificam daca suntem in colturile liniei de sus sau pe margine
    linie_sus:
    cmp ebx, 7 ; Ne aflam in coltul din dreapta sus al matricii (7,7)
    je dreapta_sus
    cmp ebx, 0 ; Ne aflam in coltul din stanga sus al matricii (7,0)
    je stanga_sus
    jmp margine_sus

    ;;Cazul in care ne aflam in coltul din dreapta sus (7,7)
    dreapta_sus:
    dec ebx ; Ne mutam cu o coloana mai jos
    dec eax ; Ne mutam cu o linie mai jos
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx 
    mov byte[ecx + eax * 8], 1 ; Punem 1 pe pozitia dorita (6,6)
    jmp final

    ;;Cazul in care ne aflam in coltul din stanga sus (7,0)
    stanga_sus:
    dec eax ; Ne mutam cu o linie mai jos
    inc ebx ; Ne mutam cu o coloana mai sus
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1 ; Punem 1 pe pozitia dorita (6,1)
    jmp final

    ;;Cazul in care ne aflam pe marginea de sus a matricii (7,X)
    margine_sus:
    ;;Avem de facut 2 shimbari
    dec eax ; Ne mutam cu o linie mai jos
    dec ebx ; Ne mutam cu o coloana mai jos
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1 ; Punem 1 pe pozitia dorita (6,X - 1)
    ;;Revenim la pozitia initiala
    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table
    dec eax ; Ne mutam cu o linie mai jos
    inc ebx ; Ne mutam cu o coloana mai sus
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1 ; Punem 1 pe pozitia dorita (6,X + 1)
    jmp final

    ;;Verificam daca suntem in colturile liniei de jos sau pe margine
    linie_jos:
    cmp ebx, 7 ; Coltul dreapta jos (0,7)
    je dreapta_jos
    cmp ebx, 0 ; Coltul stanga jos (0,0)
    je stanga_jos
    jmp margine_jos

    ;;Cazul in care ne aflam in coltul din dreapta jos (0,7)
    dreapta_jos:
    inc eax ; Ne mutam cu o linie mai sus
    dec ebx ; Ne mutam cu o coloana mai jos
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1 ; Punem 1 pe pozitia dorita (1,6)
    jmp final

    ;;Cazul in care ne aflam in coltul din stanga jos (0,0)
    stanga_jos:
    inc eax ; Ne mutam cu o linie mai sus
    inc ebx ; Ne mutam cu o coloana mai sus
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1 ; Punem 1 pe pozitia dorita (1,1)
    jmp final

    ;;Cazul in care ne aflam pe marginea de jos a matricii (0,X)
    margine_jos:
    inc eax ; Ne mutam cu o linie mai sus
    dec ebx ; Ne mutam cu o coloana mai jos
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1 ; Punem 1 pe pozitia dorita (1,1)
    ;;Revenim la pozitia initiala
    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table
    inc eax ; Ne mutam cu o linie mai sus
    inc ebx ; Ne mutam cu o coloana mai sus
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1
    jmp final

    ;Cum colturile sunt deja verificate mai avem de verificat numai marginile stanga-dreapta
    stanga_dreapta:
    cmp ebx, 0 ; Marginea din stanga (X,0)
    je margine_stanga
    cmp ebx, 7 ; Marginea din dreapta (X,7)
    je margine_dreapta
    jmp interior

    ;;Cazul in care ne aflam pe marginea din stanga matricii (X,0)
    margine_stanga:
    inc eax ; Ne mutam cu o linie mai sus
    inc ebx ; Ne mutam cu o coloana mai sus
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1
    ;;Revenim la pozitia initiala
    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table
    dec eax ; Ne mutam cu o linie mai jos
    inc ebx ; Ne mutam cu o coloana mai sus
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1
    jmp final

    ;;Cazul in care ne aflam pe marginea din dreapta matricii (X,7)
    margine_dreapta:
    inc eax ; Ne mutam cu o linie mai sus
    dec ebx ; Ne mutam cu o coloana mai jos
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1
    ;;Revenim la pozitia initiala
    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table
    dec eax ; Ne mutam cu o linie mai jos
    dec ebx ; Ne mutam cu o coloana mai jos
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1
    jmp final

    ;;Cazul in care ne aflam in interior
    interior:
    inc eax ; Ne mutam cu o linie mai sus
    inc ebx ; Ne mutam cu o coloana mai sus
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1
    ;;Revenim la pozitia initiala
    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table
    inc eax ; Ne mutam cu o linie mai sus
    dec ebx ; Ne mutam cu o coloana mai jos
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1
    ;;Revenim la pozitia initiala
    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table
    dec eax ; Ne mutam cu o linie mai jos
    inc ebx ; Ne mutam cu o coloana mai sus
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1
    ;;Revenim la pozitia initiala
    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table
    dec eax ; Ne mutam cu o linie mai jos
    dec ebx ; Ne mutam cu o coloana mai jos
    ;;Folosim formula mov byte[ecx + linie * 8 + coloana] pentru a pune 1 in matrice
    add ecx, ebx
    mov byte[ecx + eax * 8], 1
    jmp final

    final:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY