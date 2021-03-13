#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int day;
    int month;
    int year;
}date;

typedef struct { // סעיף א
    long ID;
    char* name;
    char* family;
    date DateOfBirth;
    long  partnerID;
    long  motherID;
    long  fatherID;
    unsigned char numOfChildren;
    long* childrenPtr;
}person;

typedef struct { // סעיף ג 1
    person* people;
    int size;
}db_mgr;

int cheackdate (int day ,int month ,int year,int res);
int cheackyear (int year);

void print_person(person* p) // סעיף ב
{
    int i;
    printf("ID:    %ld\n", p->ID);
    printf("first name:    %s\n", p->name);
    printf("last name:    %s\n", p->family);
    printf("date of birth:    %d.%d.%d\n", p->DateOfBirth.day, p->DateOfBirth.month, p->DateOfBirth.year);
    printf("partner ID:    %ld\n", p->partnerID);
    printf("mother ID:    %ld\n", p->motherID);
    printf("father ID:    %ld\n", p->fatherID);
    printf("number of children:    %d\n", p->numOfChildren);
    for (i = 0; i < p->numOfChildren; i++)
    {
        printf("children number %d ID:    %ld\n", i + 1, p->childrenPtr[i]);
    }
}
void init_db(db_mgr* db) // סעיף ג 2
{
    if (db->size < 1)
        return;
    db->people = (person*)calloc((db->size), sizeof(person)); // הקצאה למערך האנשים לפי מספר האנשים
}
int menu() // סעיף ד -תפריט
{
    int choose = 9;
    while (choose > 8 || choose < 1)
    {
        printf("Database System Menu:\n\n");
        printf("\t 1. Add person\n");
        printf("\t 2. Search person\n");
        printf("\t 3. search parents\n");
        printf("\t 4. Delete person\n");
        printf("\t 5. Get generation\n");
        printf("\t 6. print database\n");
        printf("\t 7. search by name\n");
        printf("\t 8. quit\n");
        scanf("%d", &choose);
        if (choose > 8 || choose < 1)
        {
            printf("oops.. wrong choice mate, please try again\n");
        }
    }
    return choose;
}
void add_person(db_mgr* db) // סעיף ה - הוספת בן אדם למאגר הנתונים
{
    
    person p;
    p.childrenPtr = NULL;
    int res=0;
    char name[20];
    printf("please insert the first name\n"); // שורה 77 עד שורה 99 - הזנת הנתונים ע"י המשתמש
    scanf("%s", name);
    p.name = (char*)malloc(strlen(name) + 1);
    strcpy(p.name, name);
    
    char family[20];
    printf("please insert the last name\n");
    scanf("%s", family);
    
    p.family = (char*)malloc(strlen(family) + 1);
    strcpy(p.family, family);
    
    printf("please insert the ID\n");
    scanf("%ld", &p.ID);
    
    printf("\n");
    
    printf("please insert the date of birth\n");
    printf("day:\t");
    scanf("%d", &p.DateOfBirth.day); printf("\n");
    
    printf("month:\t");
    scanf("%d", &p.DateOfBirth.month); printf("\n");
    
    printf("year:\t");
    scanf("%d", &p.DateOfBirth.year); printf("\n");

    int day = p.DateOfBirth.day;
    int month = p.DateOfBirth.month;
    int year = p.DateOfBirth.year;
  
    if (cheackdate(day , month , year , res) != 1)
        //בודק אם התאריך תקין אם לא הלולאה רצה שוב עד שיקלט תאריך תקין
    {
        printf("the date not vaild, please try again\n");
        
        printf("please insert the date of birth\n");
        printf("day:\t");
        scanf("%d", &p.DateOfBirth.day); printf("\n");
        
        printf("month:\t");
        scanf("%d", &p.DateOfBirth.month); printf("\n");
        
        printf("year:\t");
        scanf("%d", &p.DateOfBirth.year); printf("\n");
    }
    printf("please insert the partner ID\n");
    scanf("%ld", &p.partnerID); printf("\n");
    
    printf("please insert the mother ID\n");
    scanf("%ld", &p.motherID); printf("\n");
    
    printf("please insert the father ID\n");
    scanf("%ld", &p.fatherID); printf("\n");
    
    printf("please insert the number of children\n");
    scanf("%d", &p.numOfChildren);
    
    printf("\n");

    if (p.numOfChildren < 1)
        
     // מספר ילדים הקטן מ1 אוטומטית יוגדר כאפס
  
    {
        p.childrenPtr = NULL;
        p.numOfChildren = 0;
    }
    
    else
    {
        p.childrenPtr = (long*)malloc(p.numOfChildren * sizeof(long));
        
        // הקצאת זיכרון לת.ז של הילדים
        
        for (int i = 0; i < p.numOfChildren; i++)
        {
            printf("please insert child number %d ID\n", i + 1);
            scanf("%ld", &(p.childrenPtr[i]));
            printf("\n");
        }
    }
    int registered_citizens = 0;
    int i = 0;
    while (db->people[i].name != NULL) {
        
     // בדיקה כמה אזרחים רשומים יש מתוך מספר המקומות במערך
        
        registered_citizens++;
        i++;
    }
    if (registered_citizens < db->size) {
        
        //אם נמצא שיש פחות אזרחים רשומים ממקומות אז נוסיף את האזרח החדש ללא צורך במערך עזר
        
        if (registered_citizens == 0) {
            db->people[0] = p;
            return;
        }
        for (i = 0; i < registered_citizens; i++) {
            if (p.ID < db->people[i].ID)
                break;
        }
        for (int j = registered_citizens; j > i; j--) {
            db->people[j] = db->people[j - 1];
        }
        db->people[i] = p;
    }
    else
        
        // אחרת, ניצור מערך עזר על מנת להגדיל ב1 את המערך ולהזין את פרטי האזרח החדש
        
    {
        person* newPersons = (person*)malloc((db->size + 1) * sizeof(person));
        
        // הגדרת מערך דינאמני מסוג פרסון והקצאת זיכרון אליו
     
        int j;
        if (db->size == 0) {
            
            // אם מספר האנשים לפני ההוספה היה אפס, האיש יתווסף אוטומטית למאגר הנתונים
            
            newPersons[0] = p;
            db->people = newPersons;
            db->size = 1;
            return;
        }
        
        //סידור לפי ת״ז
        
        int index = 0;
        while (index < db->size && db->people[index].ID < p.ID) {
            newPersons[index] = db->people[index];
            index++;
        }
        newPersons[index++] = p;
        for (j = index; j < db->size + 1; j++) {
            newPersons[j] = db->people[j - 1];
        }
        db->people = newPersons;
        db->size = db->size + 1;
    }

}
int cheackdate (int day ,int month ,int year,int res)

//פונקציית עזר תאריך תקין או לא

{
     res = 0;
    
    if (day <= 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
    {
       res = 1;
    }
    else if (day <= 30 && (month == 4 || month == 6 || month == 9 || month == 11))
    {
        res = 1;
    }
    
    else if (cheackyear(year)==1) {
        if (day <= 29 && month == 2) {
            res = 1;
        }
    }
        else if (cheackyear (year) == 0)
        {
            if (day <=28 && month == 2){
                res = 1;
            }
        }
    return res;
}
    
int cheackyear (int year) //בדיקת שנה מעוברת
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return 1;
    }
    else { return 0;}
}

person* search_id(db_mgr* db, long id) //חיפוש תז בבסיס נתונים כללי סעיף ו
{
    for (int i = 0; i < db->size; i++)
    {
        if (id == db->people[i].ID)
            return &db->people[i];
    }
    return NULL;
}


void search_person(db_mgr* db) // סעיף ז
{
    long id;
   
    printf("please type the ID number of the wanted person\n");
    scanf("%ld", &id);
    
    person* res = search_id(db, id);
    if (res == NULL)
    {
        printf("ID is not found, please try again\n");
        return;
    }
    print_person(res);
}
void search_parents(db_mgr* db) // סעיף ח
{
    long id;
    printf("please type the ID number of the wanted person\n");
    scanf("%ld", &id);
    
    person* res = search_id(db, id);
    if (res == NULL)
    {
        printf("ID is not found, please try again\n");
        return;
    }
    
    if (res->fatherID == 0)
        printf("father is not found\n");
    
    else // הדפסת פרטי האבא
    {
        person* father = search_id(db, res->fatherID);
        printf("father's info:\n\n");
        print_person(father);
        printf("\n");
    }
    
    if (res->motherID == 0)
        printf("mother is not found\n");
    
    else // הדפסת פרטי האמא
    {
        person* mother = search_id(db, res->motherID);
        printf("mother's info:\n\n");
        print_person(mother);
        printf("\n");
    }
}

int  search_children(db_mgr* db, long id)
{
    for (int i = 0; i < db->size; i++)
    {
        if (id == db->people[i].ID)
            return db->people[i].numOfChildren;
    }
    return 0;
}

//void checkid

void delete_person(db_mgr* db) // סעיף ט
{
    long id;
    person* less_persons;
    
    printf("please type the ID number of the person you want to delete\n");
    scanf("%ld", &id);
    person* res = search_id(db, id);
    
    if (res == NULL)
    {
        printf("ID is not found, please try again\n");
        return;
    }
    
    less_persons = (person*)malloc((db->size - 1) * sizeof(person));
    int i = 0;
    for (i = 0; i < db->size; i++) {
        less_persons[i] = db->people[i];
        if (res->ID == db->people[i].ID)
            break;
    }
    i++;
    for (int j = i; j < db->size; j++)
    {
        less_persons[j - 1] = db->people[i];
        i++;
    }
    db->people = less_persons;
    db->size--;

    if (res->partnerID != 0)
    {
        person* partner = search_id(db, res->partnerID);
        partner->partnerID = 0;
    }
    if (res->fatherID != 0)
    {
        person* father = search_id(db, res->fatherID);
        long* less_children = (long*)malloc((father->numOfChildren - 1) * sizeof(long));
        i = 0;
        while (father->childrenPtr[i] != res->ID)
        {
            less_children[i] = father->childrenPtr[i];
            i++;
        }
        i++;
        for (int j = i; j < father->numOfChildren; j++)
        {
            less_children[j - 1] = father->childrenPtr[i];
            i++;
        }
        father->childrenPtr = less_children;
        father->numOfChildren--;
    }
    
    if (res->motherID != 0)
    {
        person* mother = search_id(db, res->motherID);
        long* less_children_1 = (long*)malloc((mother->numOfChildren - 1) * sizeof(long));
        i = 0;
        while (mother->childrenPtr[i] != res->ID)
        {
            less_children_1[i] = mother->childrenPtr[i];
            i++;
        }
        i++;
        for (int j = i; j < mother->numOfChildren; j++)
        {
            less_children_1[j - 1] = mother->childrenPtr[i];
            i++;
        }
        mother->childrenPtr = less_children_1;
        mother->numOfChildren--;
    }
    if (res->numOfChildren != 0)
    {
        for (i = 0; i < res->numOfChildren; i++)
        {
            person* child = search_id(db, res->childrenPtr[i]);
            if (child->fatherID == res->ID)
                child->fatherID = 0;
            if (child->motherID == res->ID)
                child->motherID = 0;
        }
    }
}


void get_gen(db_mgr* db)
{
    long* gen = (long*)malloc(1 * sizeof(long));
    long* gen2 = (long*)malloc(1 * sizeof(long));
    long id, childID;
    
    printf("please insert the ID of the wanted person\n");
    scanf("%ld", &id);
    
    person* res = search_id(db, id);
    if (res == NULL) {
        printf("ID is not found\n");
        return;
    }
      if (res->numOfChildren == 0) {
        printf("the generation is 1\n");
        return;
    }
    
    gen[0] = res->ID;
    int size = 1;
    int new_size = 1;
    int gen_counter = 1;
    int num_of_children;
    int total_num = 0;
    
    while (new_size != 0) {
        new_size = 0;
        total_num = 0;
        for (int i = 0; i < size; i++) {
            new_size = new_size + search_children(db, gen[i]);
        }
           if (new_size != 0) {
        
            gen_counter++; // אם צריך הקצאה לעוד מערךת הדור גדל ב-1
            gen2 = (long*)realloc(gen2, new_size * sizeof(long)); // המערך הבא יהיה בגודל סה"כ מספר הילדים שמצאנו במערך הקודם
               
               for (int i = 0; i < size; i++) {  // לולאה שרצה ובודקת למי מהמערך הקודם יש ילדים
                num_of_children = search_children(db, gen[i]); // הפונקציה מחזירה את מספר הילדים לכל ת.ז במערך
                total_num = total_num + num_of_children;
                res = search_id(db, gen[i]);
                int k = 0;
                    if (num_of_children != 0) { // במקרה שלת.ז במערך יש ילדים
                        for (int j = (total_num - num_of_children); j < total_num; j++) {
                          childID = res->childrenPtr[k];
                          gen2[j] = childID;
                          k++;
                    }
                }
            }
            gen = gen2; // עכשיו כשכל הערכים הועתקו למערך החדש אפשר לדרוס את ערכי המערך הישן
            size = new_size;
        }
    }
    
    printf("the generation is %d\n", gen_counter);
    return;
}

    void print_db(db_mgr* db) // סעיף יא
    {
        for (int i = 0; i < db->size; i++) {
            if (db->people[i].name == NULL)
                break;
            print_person(&db->people[i]);
            printf("\n---------------------------------------------\n");
        }
    }

void search_by_name(db_mgr* db)
{
    char name[20];
    char surname[20];
    int matches = 0;
    
    printf("please insert first name\n");
    scanf("%s", name);
    
    printf("please insert surname\n");
    scanf("%s", surname);
    
    for (int i = 0; i < db->size; i++)
    {
        if (db->people[i].name == NULL)
            break;
          if (strcmp(db->people[i].name, name) == 0 && strcmp(db->people[i].family, surname) == 0)
        {
            print_person(&db->people[i]);
            matches++;
        }
    }
    
            if (matches == 0) printf("the name is not in the system\n");
                return;
}

void quit(db_mgr* db)
{
    printf("thank you for for using our service, goodbye :)");
    for (int i = 0; i < db->size; i++) {
        free(db->people[i].name);
        free(db->people[i].family);
        free(db->people[i].childrenPtr);
        db->people[i].name = NULL;
        db->people[i].family = NULL;
        db->people[i].childrenPtr = NULL;
    }
    free(db->people);
    db->people = NULL;
}

void main()
{
    db_mgr d;
    
    printf("how many citizens do you want in your country?\n");
    scanf("%d", &d.size);
    
    init_db(&d);
    int choice = 0;
    printf("what would you like to do?\n\n");
    
    while (choice != 8) {
        choice = menu();
        if (choice == 1) add_person(&d);
        if (choice == 2) search_person(&d);
        if (choice == 3) search_parents(&d);
        if (choice == 4) delete_person(&d);
        if (choice == 5) get_gen(&d);
        if (choice == 6) print_db(&d);
        if (choice == 7) search_by_name(&d);
        if (choice == 8) quit(&d);
    }
}
