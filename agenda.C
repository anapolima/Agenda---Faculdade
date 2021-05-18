/*
 * Aluna: Ana Paula Oliveira de Lima
 * RA: 2312760 
 * Data de início: 14/05/2021
 * Data de término: 18/05/2021
 * Turma: ES11
 * Professor: Francisco Pereira Júnior
 * Objetivo: criar uma agenda telefônica com capacidade para 100 contatos com validação de dados
 * Configurações do sistema durante os testes do código:
 * 
 * Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/4.2.1
 * Apple clang version 12.0.5 (clang-1205.0.22.9)
 * Target: arm64-apple-darwin20.4.0
 * Thread model: posix
 * InstalledDir: /Library/Developer/CommandLineTools/usr/bin
 */

#include <stdio.h>
#include <string.h>
#define CONTACTS 100
#define NAME_LENGTH 51
#define EMAIL_LENGTH 41
#define PHONE_LENGTH 13

/* estruturas */
struct date
{
    int day;
    int month;
    int year;
};
    
struct contactInformations
{
    char name[NAME_LENGTH];
    char email[EMAIL_LENGTH];
    char phone[PHONE_LENGTH];
    struct date birthDate;
};

/* globais */
struct contactInformations contactBook[CONTACTS];
int contactBookCurrentIndex = 20;

/* protótipos */
int validateEmail (char _email[]);
int validatePhoneNumber (char _phone[]);
int validateDate (struct date);

void registerContact (struct contactInformations);
void listContacts();
void searchContactPhoneNumber (char _phone[]);
void dddOccurence(char _ddd[]);
void fill20contacts();

int main ()
{
    int answer = 0,
        checkPhone = 0,
        checkEmail = 0,
        checkDate = 0;

    char name[NAME_LENGTH],
         phone[PHONE_LENGTH],
         email[EMAIL_LENGTH];

    struct date date;
    struct contactInformations newContact;

    fill20contacts();

    printf("-------- AGENDA TELEFÔNICA --------\n");

    do
    {
        printf("1- Adicionar contato\n");
        printf("2- Listar contatos\n");
        printf("3- Pesquisar contato\n");
        printf("4- Contar contatos por DDD\n");
        printf("0- Sair\n");

        fflush(stdout);
        printf("\nEscolha: ");
        scanf("%d", &answer);
    
        switch (answer)
        {
            case 0: break;
            case 1:
                do
                {
                    getchar();
                    printf("Nome: ");
                    fgets(name, NAME_LENGTH, stdin);
                }
                while (strlen(name) < 3);
                
                // remove o \n da string
                for (int index = 0; name[index] != '\0'; index++)
                {
                    if (name[index] == '\n')
                    {
                        name[index] = '\0';
                    };
                };

                strcpy(newContact.name, name);

                do
                {
                    printf("Telefone: ");
                    fgets(phone, PHONE_LENGTH, stdin);

                    checkPhone = validatePhoneNumber(phone);
                }
                while (checkPhone != 1);
                
                // remove o \n da string
                for (int index = 0; phone[index] != '\0'; index++)
                {
                    if (phone[index] == '\n')
                    {
                        phone[index] = '\0';
                    };
                };

                strcpy(newContact.phone, phone);

                do
                {
                    getchar();
                    printf("Email: ");
                    fgets(email, EMAIL_LENGTH, stdin);

                    checkEmail = validateEmail(email);
                }
                while (checkEmail != 1);

                // remove o \n da string
                for (int index = 0; email[index] != '\0'; index++)
                {
                    if (email[index] == '\n')
                    {
                        email[index] = '\0';
                    };
                };

                strcpy(newContact.email, email);

                do
                {
                    printf("\nData de nascimento:");
                    printf("\nDia: ");
                    scanf("%d", &date.day);
                    printf("Mês: ");
                    scanf("%d", &date.month);
                    printf("Ano: ");
                    scanf("%d", &date.year);

                    checkDate = validateDate(date);
                }
                while(checkDate != 1);

                newContact.birthDate = date;

                registerContact(newContact);
            break;
            
            case 2:
                listContacts();
            break;

            case 3:
                getchar();
                printf("Insira o número de telefone do contato a ser pesquisado: ");
                fgets(phone, PHONE_LENGTH, stdin);

                searchContactPhoneNumber(phone);
            break;

            case 4:
                getchar();
                printf("Insira o DDD a ser pesquisado no formato 0XX: ");

                char ddd[4];
                fgets(ddd, 4, stdin);

                dddOccurence(ddd);
            break;

            default:
                printf("\033[1;31mOpção inválida! Tente novamente.\033[m\n\n");
            break;
        };
    }
    while (answer != 0);
};

/* função validateEmail()
 * entrada: email inserido pelo usuário
 * saída: valor 1 ou 0 caso o email seja válido ou inválido, respectivamente
 * processamento: verifica se o email tem pelo menos 2 caracteres antes do @, se o email termina com .com e quantos @ existem no email
 */
int validateEmail (char _email[30])
{
    char email[30];
    char endOfEmail[5];

    int index = 0;
    int quantityAtSign = 0,
        quantityBeforeAtSign = 0,
        difference = 0;

    strcpy(email, _email);

    for (index = 0; email[index] != '\0'; index++)
    {
        if (email[index] == '@')
        {
            quantityAtSign++;
        };
    };

    for (index = 0; email[index] != '@'; index++)
    {
        quantityBeforeAtSign++;
    };

    for (index = 0; index < strlen(email); index++)
    {
        endOfEmail[index]= email[strlen(email) - 5 + index];
    };

    difference = strncmp(endOfEmail, ".com", 4);

    if (quantityAtSign != 1 || quantityBeforeAtSign < 2 || difference != 0)
    {
        return 0;
    }
    else
    {
        return 1;
    };
};

/* função validatePhoneNumber()
 * entrada: número de telefone inserido pelo usuário
 * processamento: verifica se o número começa com 0, tem apenas números e se seu tamanho é maior que 10 e menor que 12
 * saída: valor 1 ou 0 caso o telefone seja válido ou inválido, respectivamente
 */
int validatePhoneNumber (char _phone[13])
{
    char phone[13];
    char fisrtDigit;
    int lettersQuantity = 0;
    int phoneLength = 0;

    strcpy(phone, _phone);
    
    phoneLength = strlen(phone);

    fisrtDigit = phone[0];

    // remove o \n da string
    for (int index = 0; phone[index] != '\0'; index++)
    {
        if (phone[index] == '\n')
        {
            phone[index] = '\0';
        };
    };

    for (int index = 0; phone[index] != '\0'; index++)
    {
        for (char letter = 'a'; letter <= 'z'; letter++)
        {
            if (phone[index] == letter)
            {
                lettersQuantity++;
            };
        };

        for (char letter = 'A'; letter <= 'Z'; letter++)
        {
            if (phone[index] == letter)
            {
                lettersQuantity++;
            };
        };
    };

    if (fisrtDigit != '0' || lettersQuantity != 0 || phoneLength < 12 || phoneLength > 13)
    {
        return 0;
    }
    else
    {
        return 1;
    };
};

/* função validateDate()
 * entrada: struct da data de nascimento do contato
 * processamento: verificar se a data é válida
 * entende-se por data válida: ano maior que 1900 e menor que 2021; mês maior ou igual a 1 e menor ou igual a 12;
 * dias do mês maior ou igual a 1 e menor ou igual a 30 ou 31, variando de acordo com o mês, ou ainda 
 * menor ou igual a 28 ou 29, caso o mês seja FEVEREIRO (2) e o ano seja bissexto ou não
 * saída: valor 1 ou 0 caso a data seja válido ou inválido, respectivamente
 */
int validateDate (struct date contactBirth)
{
    int day = contactBirth.day;
    int month = contactBirth.month;
    int year = contactBirth.year;

    if (year < 1900 || year > 2021)
    {
        return 0;
    }
    else
    {
        switch (month)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day <= 0 || day > 31)
                {
                    return 0;
                }
                else
                {
                    return 1;
                };
            break;

            case 4:
            case 6:
            case 9:
            case 11:
                if (day <= 0 || day > 30)
                {
                    return 0;
                }
                else
                {
                    return 1;
                };
            break;

            case 2:
                if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                {
                    if (day <= 0 || day > 29)
                    {
                        return 0;
                    }
                    else
                    {
                        return 1;
                    };
                }
                else
                {
                    if (day <= 0 || day > 28)
                    {
                        return 0;
                    }
                    else
                    {
                        return 1;
                    };
                };
                break;
    
            default:
                return 0;
            break;
        };
    };
};

/* função registerContact()
 * entrada: struct do contato a ser adicionado à agenda
 * processamento: adicionar o contato à agenda
 */
void registerContact (struct contactInformations _contact)
{
    contactBook[contactBookCurrentIndex] = _contact;
    contactBookCurrentIndex++;

    printf("\nContato adicionado com sucesso!\n\n");
};

/* função listContacts()
 * processamento: listar nome, email e telefone de todos os contatos da agenda em ordem alfabética de nome
 * optei por fazer uma cópia da lista original para fazer a ordenação para que a original não fosse alterada
 */
void listContacts (void)
{
    struct contactInformations auxiliarContactBook[CONTACTS];

    // faz a cópia da lista original
    for (int index = 0; index < contactBookCurrentIndex; index++)
    {
        auxiliarContactBook[index] = contactBook[index];
    };

    // faz a ordenação da lista auxiliar
    for (int index = 0; index < contactBookCurrentIndex; index++)
    {
        for (int auxIndex = 0; auxIndex < contactBookCurrentIndex - 1; auxIndex++)
        {
            char auxiliarName1[NAME_LENGTH];
            strcpy(auxiliarName1, auxiliarContactBook[index].name);

            char auxiliarName2[NAME_LENGTH];
            strcpy(auxiliarName2, auxiliarContactBook[auxIndex].name);
            
            if (strcasecmp(auxiliarContactBook[index].name, auxiliarContactBook[auxIndex].name) < 0)
            {
                struct contactInformations aux;
                aux = auxiliarContactBook[index];
                auxiliarContactBook[index] = auxiliarContactBook[auxIndex];
                auxiliarContactBook[auxIndex] = aux;
            };
        };
    };

    // exibe a lista auxiliar ordenada
    for (int index = 0; index < contactBookCurrentIndex; index++)
    {
        if (index == 0)
        {
            printf("\n%-51s | %-14s | %-41s\n", "NOME", "TELEFONE", "EMAIL");
        };

        printf("%-51s | %-14s | %-41s\n", auxiliarContactBook[index].name, auxiliarContactBook[index].phone, auxiliarContactBook[index].email);
    };
    printf("\n");
};

/* função searchContactPhoneNumber()
 * entrada: número de telefone a ser procurado na agenda
 * saída: todos os dados do contato que possui esse número de telefone
 * processamento: verificar se há na lista de contatos algum contato com o número de telefone igual ao recebido
 */
void searchContactPhoneNumber (char _phone[13])
{
    char phone[13];
    int foundContacts = 0;

    strcpy(phone, _phone);

    for (int index = 0; index < contactBookCurrentIndex; index++)
    {
        if (strcmp(contactBook[index].phone, phone) == 0)
        {
            foundContacts++;

            if (foundContacts == 1)
            {
                printf("\n%-51s | %-15s | %-41s | DATA DE NASCIMENTO\n", "NOME", "TELEFONE", "EMAIL");
            };

            printf("%-51s | %-15s | %-41s | %d/%d/%d\n", contactBook[index].name, contactBook[index].phone, contactBook[index].email, contactBook[index].birthDate.day, contactBook[index].birthDate.month, contactBook[index].birthDate.year);
        };
    };

    if (foundContacts == 0)
    {
        printf("\nNão há nenhum contato com este número de telefone!\n");
    };

    printf("\n");
};

/* função dddOccurence()
 * entrada: DDD a ser pesquisado, formato 0XX
 * saída: quantidade de contatos na agenda que possuem o DDD pesquisado
 * processamento: comparar os 3 primeiros dígitos do número de telefone de cada contato com o DDD a ser pesquisado
 */
// como, diferentemente das outras funções, o pdf não especificava que deveira ter um retorno, subentendi que era pra ser uma função sem retorno
void dddOccurence(char _ddd[4])
{
    char ddd[4];
    int dddOccurence = 0;

    strcpy(ddd, _ddd);

    for (int index = 0; index < contactBookCurrentIndex; index++)
    {
        if (strncmp(contactBook[index].phone, ddd, 3) == 0)
        {
            dddOccurence++;
        };
    };

    if (dddOccurence == 0)
    {
        printf("\nNão há nenhum contato com o DDD informado!\n");
    }
    else if (dddOccurence == 1)
    {
        printf("\nxiste 1 contato com o DDD informado\n");
    }
    else
    {
        printf("\nExistem %d contatos com o DDD informado\n", dddOccurence);
    };

    printf("\n");
};

/* função fill20contacts()
 * processamento: adicionar 20 contatos à agenda
 */
void fill20contacts ()
{
    strcpy(contactBook[0].name, "Eduarda");
    strcpy(contactBook[0].phone, "014998443566");
    strcpy(contactBook[0].email, "eduarda@gmail.com");
    contactBook[0].birthDate.day = 4;
    contactBook[0].birthDate.month = 4;
    contactBook[0].birthDate.year = 2008;

    strcpy(contactBook[1].name, "Daniela");
    strcpy(contactBook[1].phone, "030907281622");
    strcpy(contactBook[1].email, "daniela@gmail.com");
    contactBook[1].birthDate.day = 3;
    contactBook[1].birthDate.month = 10;
    contactBook[1].birthDate.year = 2004;

    strcpy(contactBook[2].name, "Carolina");
    strcpy(contactBook[2].phone, "089948462205");
    strcpy(contactBook[2].email, "carolina@gmail.com");
    contactBook[2].birthDate.day = 18;
    contactBook[2].birthDate.month = 11;
    contactBook[2].birthDate.year = 2007;

    strcpy(contactBook[3].name, "Mia");
    strcpy(contactBook[3].phone, "078943569145");
    strcpy(contactBook[3].email, "mia@gmail.com");
    contactBook[3].birthDate.day = 23;
    contactBook[3].birthDate.month = 9;
    contactBook[3].birthDate.year = 2013;

    strcpy(contactBook[4].name, "Layra");
    strcpy(contactBook[4].phone, "062920060940");
    strcpy(contactBook[4].email, "layra@gmail.com");
    contactBook[4].birthDate.day = 10;
    contactBook[4].birthDate.month = 5;
    contactBook[4].birthDate.year = 2006;

    strcpy(contactBook[5].name, "Clara");
    strcpy(contactBook[5].phone, "081949047509");
    strcpy(contactBook[5].email, "clara@gmail.com");
    contactBook[5].birthDate.day = 16;
    contactBook[5].birthDate.month = 7;
    contactBook[5].birthDate.year = 2003;

    strcpy(contactBook[6].name, "Lia");
    strcpy(contactBook[6].phone, "066920988192");
    strcpy(contactBook[6].email, "lia@gmail.com");
    contactBook[6].birthDate.day = 4;
    contactBook[6].birthDate.month = 4;
    contactBook[6].birthDate.year = 2008;

    strcpy(contactBook[7].name, "Nayr");
    strcpy(contactBook[7].phone, "077912964371");
    strcpy(contactBook[7].email, "nayr@gmail.com");
    contactBook[7].birthDate.day = 4;
    contactBook[7].birthDate.month = 4;
    contactBook[7].birthDate.year = 2008;

    strcpy(contactBook[8].name, "Dante");
    strcpy(contactBook[8].phone, "062929790089");
    strcpy(contactBook[8].email, "dante@gmail.com");
    contactBook[8].birthDate.day = 4;
    contactBook[8].birthDate.month = 12;
    contactBook[8].birthDate.year = 2008;

    strcpy(contactBook[9].name, "Amanda");
    strcpy(contactBook[9].phone, "043914360447");
    strcpy(contactBook[9].email, "amanda@gmail.com");
    contactBook[9].birthDate.day = 13;
    contactBook[9].birthDate.month = 1;
    contactBook[9].birthDate.year = 2005;

    strcpy(contactBook[10].name, "Simone");
    strcpy(contactBook[10].phone, "078902784729");
    strcpy(contactBook[10].email, "simone@gmail.com");
    contactBook[10].birthDate.day = 4;
    contactBook[10].birthDate.month = 4;
    contactBook[10].birthDate.year = 2008;

    strcpy(contactBook[11].name, "Nilo");
    strcpy(contactBook[11].phone, "071960744910");
    strcpy(contactBook[11].email, "nilo@gmail.com");
    contactBook[11].birthDate.day = 19;
    contactBook[11].birthDate.month = 1;
    contactBook[11].birthDate.year = 2008;

    strcpy(contactBook[12].name, "Eliana");
    strcpy(contactBook[12].phone, "031913537060");
    strcpy(contactBook[12].email, "eliana@gmail.com");
    contactBook[12].birthDate.day = 29;
    contactBook[12].birthDate.month = 10;
    contactBook[12].birthDate.year = 2009;

    strcpy(contactBook[13].name, "Stephany");
    strcpy(contactBook[13].phone, "059998780030");
    strcpy(contactBook[13].email, "stephany@gmail.com");
    contactBook[13].birthDate.day = 29;
    contactBook[13].birthDate.month = 9;
    contactBook[13].birthDate.year = 2005;

    strcpy(contactBook[14].name, "David");
    strcpy(contactBook[14].phone, "038979393771");
    strcpy(contactBook[14].email, "david@gmail.com");
    contactBook[14].birthDate.day = 23;
    contactBook[14].birthDate.month = 12;
    contactBook[14].birthDate.year = 2006;

    strcpy(contactBook[15].name, "Lana");
    strcpy(contactBook[15].phone, "023976774076");
    strcpy(contactBook[15].email, "lana@gmail.com");
    contactBook[15].birthDate.day = 25;
    contactBook[15].birthDate.month = 5;
    contactBook[15].birthDate.year = 2000;

    strcpy(contactBook[16].name, "Mel");
    strcpy(contactBook[16].phone, "085945377239");
    strcpy(contactBook[16].email, "mel@gmail.com");
    contactBook[16].birthDate.day = 7;
    contactBook[16].birthDate.month = 1;
    contactBook[16].birthDate.year = 2004;

    strcpy(contactBook[17].name, "Helder");
    strcpy(contactBook[17].phone, "043980497504");
    strcpy(contactBook[17].email, "helder@gmail.com");
    contactBook[17].birthDate.day = 6;
    contactBook[17].birthDate.month = 2;
    contactBook[17].birthDate.year = 2006;

    strcpy(contactBook[18].name, "Brian");
    strcpy(contactBook[18].phone, "033945437839");
    strcpy(contactBook[18].email, "brian@gmail.com");
    contactBook[18].birthDate.day = 11;
    contactBook[18].birthDate.month = 3;
    contactBook[18].birthDate.year = 2003;

    strcpy(contactBook[19].name, "Lunna");
    strcpy(contactBook[19].phone, "061975236016");
    strcpy(contactBook[19].email, "lunna@gmail.com");
    contactBook[19].birthDate.day = 28;
    contactBook[19].birthDate.month = 9;
    contactBook[19].birthDate.year = 2001;
};
