section .text

global _start
global hash_crc32_asm

; --------------------------------------------------------
; Return hash of value
; Args: rsi - length of data to hash
;      rdi - address of data to hash
;
; Returns: rax - hash of value
;
; Destr: rax, rcx
; --------------------------------------------------------
hash_crc32_asm:
    xor rax, rax;
    mov rax, 0x1EDC6F41 ; initial value

    cmp rsi, 31
    ja .end_of_func

    ; rsi = length
    ; jmp [jt_length_of_hash + rsi * 8]
    lea rcx, [rel .jt_length_of_hash]
    mov rsi, [rcx + rsi * 8]
    add rsi, rcx
    jmp rsi

.jt_length_of_hash:
    dq .len0  - .jt_length_of_hash
    dq .len1  - .jt_length_of_hash
    dq .len2  - .jt_length_of_hash
    dq .len3  - .jt_length_of_hash
    dq .len4  - .jt_length_of_hash
    dq .len5  - .jt_length_of_hash
    dq .len6  - .jt_length_of_hash
    dq .len7  - .jt_length_of_hash
    dq .len8  - .jt_length_of_hash
    dq .len9  - .jt_length_of_hash
    dq .len10 - .jt_length_of_hash
    dq .len11 - .jt_length_of_hash
    dq .len12 - .jt_length_of_hash
    dq .len13 - .jt_length_of_hash
    dq .len14 - .jt_length_of_hash
    dq .len15 - .jt_length_of_hash
    dq .len16 - .jt_length_of_hash
    dq .len17 - .jt_length_of_hash
    dq .len18 - .jt_length_of_hash
    dq .len19 - .jt_length_of_hash
    dq .len20 - .jt_length_of_hash
    dq .len21 - .jt_length_of_hash
    dq .len22 - .jt_length_of_hash
    dq .len23 - .jt_length_of_hash
    dq .len24 - .jt_length_of_hash
    dq .len25 - .jt_length_of_hash
    dq .len26 - .jt_length_of_hash
    dq .len27 - .jt_length_of_hash
    dq .len28 - .jt_length_of_hash
    dq .len29 - .jt_length_of_hash
    dq .len30 - .jt_length_of_hash
    dq .len31 - .jt_length_of_hash

.len31: crc32 eax, byte [rdi + 30]
.len30: crc32 eax, byte [rdi + 29]
.len29: crc32 eax, byte [rdi + 28]
.len28: crc32 eax, byte [rdi + 27]
.len27: crc32 eax, byte [rdi + 26]
.len26: crc32 eax, byte [rdi + 25]
.len25: crc32 eax, byte [rdi + 24]
.len24: crc32 eax, byte [rdi + 23]
.len23: crc32 eax, byte [rdi + 22]
.len22: crc32 eax, byte [rdi + 21]
.len21: crc32 eax, byte [rdi + 20]
.len20: crc32 eax, byte [rdi + 19]
.len19: crc32 eax, byte [rdi + 18]
.len18: crc32 eax, byte [rdi + 17]
.len17: crc32 eax, byte [rdi + 16]
.len16: crc32 eax, byte [rdi + 15]
.len15: crc32 eax, byte [rdi + 14]
.len14: crc32 eax, byte [rdi + 13]
.len13: crc32 eax, byte [rdi + 12]
.len12: crc32 eax, byte [rdi + 11]
.len11: crc32 eax, byte [rdi + 10]
.len10: crc32 eax, byte [rdi + 9]
.len9:  crc32 eax, byte [rdi + 8]
.len8:  crc32 eax, byte [rdi + 7]
.len7:  crc32 eax, byte [rdi + 6]
.len6:  crc32 eax, byte [rdi + 5]
.len5:  crc32 eax, byte [rdi + 4]
.len4:  crc32 eax, byte [rdi + 3]
.len3:  crc32 eax, byte [rdi + 2]
.len2:  crc32 eax, byte [rdi + 1]
.len1:  crc32 eax, byte [rdi]
.len0:
.end_of_func:
    nop
    ret

section .data:
