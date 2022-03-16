# Sécurité TP 1

## Contexte 

Travail dans le terminal -> "Dans la VM Docker"

### Exercice 1

#### Consigne :

Se rendre dans le répertoire niveau 1 et retrouver le mot de passe

```console
cd niveau1
gdb ./niveau1
```


```console
gdb-peda$ pdisass main
Dump of assembler code for function main:
   0x080484c4 <+0>:     push   ebp
   0x080484c5 <+1>:     mov    ebp,esp
   0x080484c7 <+3>:     push   ebx
   0x080484c8 <+4>:     and    esp,0xfffffff0
   0x080484cb <+7>:     sub    esp,0x40
   0x080484ce <+10>:    mov    eax,DWORD PTR [ebp+0xc]
   0x080484d1 <+13>:    mov    DWORD PTR [esp+0x1c],eax
   0x080484d5 <+17>:    mov    eax,gs:0x14
   0x080484db <+23>:    mov    DWORD PTR [esp+0x3c],eax
   0x080484df <+27>:    xor    eax,eax
   0x080484e1 <+29>:    mov    DWORD PTR [esp+0x24],0x0
   0x080484e9 <+37>:    mov    eax,0x80486cc
   0x080484ee <+42>:    mov    DWORD PTR [esp],eax
   0x080484f1 <+45>:    call   0x80483a0 <printf@plt>
   0x080484f6 <+50>:    mov    eax,0x80486fc
   0x080484fb <+55>:    mov    DWORD PTR [esp],eax
   0x080484fe <+58>:    call   0x80483a0 <printf@plt>
   0x08048503 <+63>:    mov    eax,0x80486cc
   0x08048508 <+68>:    mov    DWORD PTR [esp],eax
   0x0804850b <+71>:    call   0x80483a0 <printf@plt>
   0x08048510 <+76>:    mov    eax,0x804872c
   0x08048515 <+81>:    mov    DWORD PTR [esp],eax
   0x08048518 <+84>:    call   0x80483a0 <printf@plt>
   0x0804851d <+89>:    mov    eax,0x804875c
   0x08048522 <+94>:    mov    DWORD PTR [esp],eax
   0x08048525 <+97>:    call   0x80483a0 <printf@plt>
   0x0804852a <+102>:   mov    eax,0x804878a
   0x0804852f <+107>:   mov    DWORD PTR [esp],eax
   0x08048532 <+110>:   call   0x80483a0 <printf@plt>
   0x08048537 <+115>:   mov    eax,ds:0x804a024
   0x0804853c <+120>:   mov    DWORD PTR [esp+0x8],eax
   0x08048540 <+124>:   mov    DWORD PTR [esp+0x4],0x14
   0x08048548 <+132>:   lea    eax,[esp+0x28]
   0x0804854c <+136>:   mov    DWORD PTR [esp],eax
   0x0804854f <+139>:   call   0x80483b0 <fgets@plt>
   0x08048554 <+144>:   lea    eax,[esp+0x28]
   0x08048558 <+148>:   mov    DWORD PTR [esp],eax
   0x0804855b <+151>:   call   0x80483e0 <strlen@plt>
   0x08048560 <+156>:   sub    eax,0x1
   0x08048563 <+159>:   mov    DWORD PTR [esp+0x24],eax
   0x08048567 <+163>:   mov    ebx,DWORD PTR [esp+0x24]
   0x0804856b <+167>:   mov    DWORD PTR [esp],0x80486c0
   0x08048572 <+174>:   call   0x80483e0 <strlen@plt>
   0x08048577 <+179>:   cmp    ebx,eax
   0x08048579 <+181>:   je     0x8048594 <main+208>
   0x0804857b <+183>:   mov    eax,0x80487a4
   0x08048580 <+188>:   mov    DWORD PTR [esp],eax
   0x08048583 <+191>:   call   0x80483a0 <printf@plt>
   0x08048588 <+196>:   mov    DWORD PTR [esp],0x0
   0x0804858f <+203>:   call   0x80483d0 <exit@plt>
   0x08048594 <+208>:   mov    DWORD PTR [esp],0x80486c0
   0x0804859b <+215>:   call   0x80483e0 <strlen@plt>
   0x080485a0 <+220>:   mov    DWORD PTR [esp+0x8],eax
   0x080485a4 <+224>:   lea    eax,[esp+0x28]
   0x080485a8 <+228>:   mov    DWORD PTR [esp+0x4],eax
   0x080485ac <+232>:   mov    DWORD PTR [esp],0x80486c0
   0x080485b3 <+239>:   call   0x8048400 <strncmp@plt>
   0x080485b8 <+244>:   test   eax,eax
   0x080485ba <+246>:   jne    0x80485d5 <main+273>
   0x080485bc <+248>:   mov    eax,0x80487e0
   0x080485c1 <+253>:   mov    DWORD PTR [esp],eax
   0x080485c4 <+256>:   call   0x80483a0 <printf@plt>
   0x080485c9 <+261>:   mov    DWORD PTR [esp],0x0
   0x080485d0 <+268>:   call   0x80483d0 <exit@plt>
   0x080485d5 <+273>:   mov    eax,0x8048809
   0x080485da <+278>:   mov    DWORD PTR [esp],eax
   0x080485dd <+281>:   call   0x80483a0 <printf@plt>
   0x080485e2 <+286>:   mov    DWORD PTR [esp],0x0
   0x080485e9 <+293>:   call   0x80483d0 <exit@plt>
End of assembler dump.
```

On met un Breakpoint au niveau de l'appel de la fonction strcmp()

```console
gdb-peda$ Break * 0x080485b3
gdb-peda$ run
Starting program: /home/etudiant/niveau1/niveau1
###########################################
############      Exercice 1      #########
###########################################
##  Objectif : Retrouver le bon MDP      ##
###########################################
 [----------------------------------registers-----------------------------------]
EAX: 0xfffda888 ("password\n")
EBX: 0x8
ECX: 0x0
EDX: 0x8
ESI: 0x0
EDI: 0x0
EBP: 0xfffda8a8 --> 0x0
ESP: 0xfffda860 --> 0x80486c0 ("MeG@pass")
EIP: 0x80485b3 (<main+239>:     call   0x8048400 <strncmp@plt>)
EFLAGS: 0x202 (carry parity adjust zero sign trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
   0x80485a4 <main+224>:        lea    eax,[esp+0x28]
   0x80485a8 <main+228>:        mov    DWORD PTR [esp+0x4],eax
   0x80485ac <main+232>:        mov    DWORD PTR [esp],0x80486c0
=> 0x80485b3 <main+239>:        call   0x8048400 <strncmp@plt>
   0x80485b8 <main+244>:        test   eax,eax
   0x80485ba <main+246>:        jne    0x80485d5 <main+273>
   0x80485bc <main+248>:        mov    eax,0x80487e0
   0x80485c1 <main+253>:        mov    DWORD PTR [esp],eax
Guessed arguments:
arg[0]: 0x80486c0 ("MeG@pass")
arg[1]: 0xfffda888 ("password\n")
arg[2]: 0x8
[------------------------------------stack-------------------------------------]
0000| 0xfffda860 --> 0x80486c0 ("MeG@pass")
0004| 0xfffda864 --> 0xfffda888 ("password\n")
0008| 0xfffda868 --> 0x8
0012| 0xfffda86c --> 0x8048381 (<_init+41>:     add    esp,0x8)
0016| 0xfffda870 --> 0xfffdb983 ("/home/etudiant/niveau1/niveau1")
0020| 0xfffda874 --> 0x2f ('/')
0024| 0xfffda878 --> 0x8049ff4 --> 0x8049f28 --> 0x1
0028| 0xfffda87c --> 0xfffda944 --> 0xfffdb983 ("/home/etudiant/niveau1/niveau1")
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value

Breakpoint 3, 0x080485b3 in main ()
```

On voit bien que le code s'arrête au niveau de l'instruction strcmp() et permet de voir les arguments passés à la fonction de comparaison, et on voit "MeG@pass" stocké à l'adresse 0x80486c0 (On peut aussi visualiser le contenu en mémoire à cette adresse en utilisant le commande x/2s), il s'agit du mot de passe avec lequel est comparé ce qu'on a rentré, qui est stocké dans le registre EAX, c'est donc le mot de passe maître du programme.

### Exercice 2

#### Consigne :

Utilisation de la commande ni dans gdb pour passer chaque instruction pas à pas


On voit que le mot de passe est de longueur 9 :

```console
0x080485bb <+215>:   cmp    DWORD PTR [esp+0x28],0x9
```


On observe la présence de 9 instructions de remplissage : 

```console
0x08048500 <+28>:    mov    BYTE PTR [esp+0x43],0x62
0x08048505 <+33>:    mov    BYTE PTR [esp+0x44],0x75
0x0804850a <+38>:    mov    BYTE PTR [esp+0x45],0x6c
0x0804850f <+43>:    mov    BYTE PTR [esp+0x46],0x6c
0x08048514 <+48>:    mov    BYTE PTR [esp+0x47],0x24
0x08048519 <+53>:    mov    BYTE PTR [esp+0x48],0x68
0x0804851e <+58>:    mov    BYTE PTR [esp+0x49],0x69
0x08048523 <+63>:    mov    BYTE PTR [esp+0x4a],0x74
0x08048528 <+68>:    mov    BYTE PTR [esp+0x4b],0x21
```


Les 9 valeurs héxadécimales à la fin de chaque instructions sont concaténées et deviennent la chaîne de char : 'bull$hit'



### Exercice 3

#### Consigne :

Trouver le mot de passe du niveau 3

On sait que le mot de passe est long de 14 char, auxquels sont aplliqués un XOR. En appliquant un décodage XOR avec la clé 0xFE, on obtient "xorebull$hit"

### Exercice 4 

#### Consigne : 

Se rendre dans le répertoire «niveau4» et exploiter le binaire pour:

1 / Appeler la fonction «callMeMaybe» (Celle-ci n’est pas utilisée  par le programme).

2 / Obtenir un shell «root»
