#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma warning(disable:4996)
#define SIZE 50
//Struktura z danymi osobowymi
struct Dane
{
	char* imie;
	char* nazwisko;
	int wiek;
	long long int PESEL;
	char gender;
};

//Struktura z lista dwukierunkowa

struct Osoba
{
	struct Dane dane;
	struct Osoba* next;
	struct Osoba* prev;
};

struct Osoba* head = NULL;

void clrscr()
{
	system("cls");
}

struct Osoba* Add()
{
	struct Osoba *element;
	char bufor[SIZE];
	char *imie, *nazwisko;
	char gender;
	int wiek;
	long long int PESEL;

	printf("Imie: ");
	scanf("%s", &bufor);
	imie = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
	strcpy(imie, bufor);

	printf("Nazwisko: ");
	scanf("%s", &bufor);
	nazwisko = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
	strcpy(nazwisko, bufor);


	printf("Wiek: ");
	scanf("%d", &wiek);

	printf("PESEL: ");
	scanf("%lld", &PESEL);

	printf("K/M?: ");
	scanf(" %c", &gender);

	if (head == NULL)
	{
		head = (struct Osoba*)malloc(sizeof(struct Osoba));
		head->next = NULL;
		head->prev = NULL;
		head->dane.imie = imie;
		head->dane.nazwisko = nazwisko;
		head->dane.wiek = wiek;
		head->dane.PESEL = PESEL;
		head->dane.gender = gender;
		clrscr();
		printf("Pomyslnie dodano osobe do listy\n\n");
		return;
	}
	struct Osoba* tmp, *prevPrev;
	tmp = head;
	prevPrev = NULL;
	do 
	{
		prevPrev = tmp;
		tmp = tmp->next;
	} while (tmp != NULL);

	tmp = (struct Osoba*)malloc(sizeof(struct Osoba));
	tmp->next = NULL;
	tmp->prev = prevPrev;
	tmp->prev->next = tmp;
	tmp->dane.imie = imie;
	tmp->dane.nazwisko = nazwisko;
	tmp->dane.wiek = wiek;
	tmp->dane.PESEL = PESEL;
	tmp->dane.gender = gender;

	clrscr();
	printf("Pomyslnie dodano osobe do listy\n\n");
}
void Search(char*name)
{
	if (head == NULL)
	{
		printf("Lista jest pusta\n\n");
	}
	else
	{
		struct Osoba* tmp;
		tmp = head;
		while (tmp != NULL) {

			if (!strcmp(tmp->dane.nazwisko, name))
			{
				printf("Znaleziono szukana osobe\n\n");
				printf("     Imie: %s\n", tmp->dane.imie);
				printf(" Nazwisko: %s\n", tmp->dane.nazwisko);
				printf("     Wiek: %d\n", tmp->dane.wiek);
				printf("    PESEL: %lld\n", tmp->dane.PESEL);
				printf("      K/M: %c\n\n", tmp->dane.gender);
				break;
			}
			tmp = tmp->next;
		}

		if (tmp == NULL)
			printf("Szukana osoba nie istnieje\n\n");
	}
}

void Delete(char* name) {
	struct Osoba* tmp;

	if (!strcmp(head->dane.nazwisko, name) && head->next == NULL)//przypadek gdy lista zawiera tylko 1 element (nie chcemy sie odwolac do NULLa)
	{
		free(head->dane.imie);
		free(head->dane.nazwisko);
		free(head);
		head = NULL;
		printf("Pomyslnie usunieto osobe z listy\n\n");
		return;
	}
	if (!strcmp(head->dane.nazwisko, name) && (head->prev == NULL&& head->next != NULL))
	{
		tmp = head;
		head = head->next;
		free(tmp->dane.imie);
		free(tmp->dane.nazwisko);
		free(tmp);
		printf("Pomyslnie usunieto osobe z listy\n\n");
		return;
	}
	tmp = head;
	while (tmp != NULL)
	{
		if (!strcmp(tmp->dane.nazwisko, name))
		{
			if (tmp->next == NULL)
			{
				tmp->prev->next = NULL;
			}
			else 
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			free(tmp->dane.imie);
			free(tmp->dane.nazwisko);
			free(tmp);
			printf("Pomyslnie usunieto osobe z listy\n\n");
			return;
		}
		tmp = tmp->next;
	}
}

void Show() {
	if (head == NULL)
	{
		printf("Lista jest pusta\n\n");
		return;
	}
	struct Osoba* tmp;
	tmp = head;
	printf("___________________________________________________________________\n");
	printf("||     Imie      ||    Nazwisko    || Wiek ||    PESEL    || K/M ||\n");
	printf("-------------------------------------------------------------------\n");
	while (tmp != NULL) 
	{

		printf("|| %13s |", tmp->dane.imie);
		printf("|%15s |", tmp->dane.nazwisko);
		printf("|%4d  |", tmp->dane.wiek);
		printf("|%12lld |", tmp->dane.PESEL);
		printf("|  %c  ||\n", tmp->dane.gender);

		tmp = tmp->next;
	}
	printf("-------------------------------------------------------------------\n\n");
}

void Read() {
	FILE *sstream = NULL;
	char bufor[SIZE];
	int bufor1;
	long long int bufor3;
	char bufor2;
	struct Osoba *tmp, *tmp2;

	sstream = fopen("input.txt", "r");
	if (sstream == NULL)
		printf("Blad otwarcia pliku\n\n");
	else
	{
		while (fscanf(sstream, "%s", bufor) != EOF)
		{
			tmp = (struct Osoba*)malloc(sizeof(struct Osoba));

			tmp->dane.imie = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(tmp->dane.imie, bufor);

			fscanf(sstream, "%s", bufor);
			tmp->dane.nazwisko = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(tmp->dane.nazwisko, bufor);

			fscanf(sstream, "%d", &bufor1);
			tmp->dane.wiek = bufor1;

			fscanf(sstream, "%lld", &bufor3);
			tmp->dane.PESEL = bufor3;

			fscanf(sstream, " %c", &bufor2);
			tmp->dane.gender = bufor2;

			if (head == NULL)
			{
				head = tmp;
				tmp->prev = NULL;
				tmp->next = NULL;
			}
			else
			{
				tmp2 = head;
				while (tmp2->next != NULL) 
				{
					tmp2 = tmp2->next;
				}
				tmp->prev = tmp2;
				tmp->next = NULL;
				tmp2->next = tmp;
			}
		}
		printf("Plik zostal wczytany\n\n");
	}
	fclose(sstream);
}

void Save() {
	FILE *sstream = NULL;
	struct Osoba *tmp;

	if (head == NULL)
		printf("Nie ma elementow do zapisania\n\n");
	else
	{
		sstream = fopen("input.txt", "w");
		if (sstream == NULL)
			printf("Blad otwarcia pliku\n\n");
		else
		{
			tmp = head;
			while (tmp != NULL)
			{
				fprintf(sstream, "%s ", tmp->dane.imie);
				fprintf(sstream, "%s ", tmp->dane.nazwisko);
				fprintf(sstream, "%d ", tmp->dane.wiek);
				fprintf(sstream, "%lld ", tmp->dane.PESEL);
				fprintf(sstream, "%c\n", tmp->dane.gender);
				tmp = tmp->next;
			}
			printf("Lista zostala zapisana\n\n");
		}
		fclose(sstream);
	}
}

void Sort() {
	struct Osoba *tmp, *tmp2, *tmp3;
	bool sorted = NULL;

	if (head == NULL)
		printf("Lista jest pusta.\n\n");

	tmp = head;
	tmp2 = head;
	tmp3 = head;

	while (tmp3->next != NULL) 
	{
		while (tmp->next != NULL) 
		{
			if (strcmp(tmp2->dane.nazwisko, tmp->next->dane.nazwisko) > 0)
				tmp2 = tmp->next;
			tmp = tmp->next;
		}
		if (tmp2 != tmp3) 
		{
			tmp2->prev->next = tmp2->next;
			if (tmp3->prev != NULL)
				tmp3->prev->next = tmp2;
			else
				head = tmp2;
			if (tmp2->next != NULL)
				tmp2->next->prev = tmp2->prev;
			tmp2->prev = tmp3->prev;
			tmp2->next = tmp3;
			tmp3->prev = tmp2;
		}
		tmp2 = tmp2->next;
		tmp3 = tmp2;
		tmp = tmp2;
	}
	printf("Sortowanie listy ukonczone\n\n");

}

void DeleteALL() {
	struct Osoba *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->dane.imie);
		free(tmp->dane.nazwisko);
		free(tmp);
	}
	printf("Lista zostala wyczyszczona\n\n");
}

void printmenu()
{
	printf("1. Dodaj osobe\n");
	printf("2. Wyszukaj osobe\n");
	printf("3. Skasuj osobe\n");
	printf("4. Wyswietl liste\n");
	printf("5. Pobierz liste z pliku\n");
	printf("6. Zapisz liste do pliku\n");
	printf("7. Sortowanie listy\n");
	printf("8. Wyczysc liste\n\n");
	printf("0. EXIT\n\n");
	printf("Wybierz polecenie: ");
}
int main() {
	int menu;
	char bufor[50];
	char*name = 48;

	while (1)
	{
		printmenu();
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:			//Dodawanie osoby do listy
			clrscr();
			Add();
			break;

		case 2:			//Wyszukiwanie osoby po nazwisku
			clrscr();
			printf("Podaj nazwisko szukanej osoby\n");
			scanf("%s", &bufor);
			name = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(name, bufor);
			Search(name);
			free(name);
			break;

		case 3:			//Kasowanie osoby po nazwisku
			clrscr();
			printf("Podaj nazwisko osoby do usuniecia\n");
			scanf("%s", &bufor);
			name = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(name, bufor);
			Delete(name);
			free(name);
			break;

		case 4:			//Wyswietlanie listy
			clrscr();
			Show();
			break;

		case 5:			//Odczytywanie listy z pliku
			clrscr();
			Read();
			break;

		case 6:			//Zapis listy do pliku
			clrscr();
			Save();
			break;

		case 7:			//Sortowanie listy
			clrscr();
			Sort();
			break;

		case 8:			//Sortowanie listy
			clrscr();
			DeleteALL();
			break;

		case 0:			//Exit
			clrscr();
			DeleteALL();
			return(0);
			break;

		default:
			clrscr();
			printf("Wybrano niepoprawny numer, wybierz  ponownie\n\n");
			break;
		}
	}
}