#include<stdio.h>
#include<stdlib.h>

typedef struct student{
    float   grade;
    int    id;
    struct student* next;
}student;

student* createStudent(int id, float grade){
    student* newStudent = (student*)malloc(sizeof(student));
    newStudent->id = id;
    newStudent->grade = grade;
    newStudent->next = NULL;
    return newStudent;
}

void initializeList(student** head, int n){
    for (int i = 0; i < n; i++){
        student* newStudent= (student*)malloc(sizeof(student));
        newStudent = createStudent(0, 0.0);
        newStudent->next = *head;
        *head = newStudent;
    }
}
void removeInitializations(student** head){
    student* current = *head;
    while(current -> next != NULL && current -> id == 0 && current -> grade == 0.0){
        student* temp = current;
        current = current -> next;
        free(temp);
    }
    *head = current;
}

void addStudentSorted(student** head, int id, float grade){
    student* newStudent = createStudent(id, grade);
    if (*head == NULL || (*head)->grade >= newStudent->grade)
    {
        newStudent->next = *head;
        *head = newStudent;
    } else {
        student* current= *head;
        while (current->next != NULL && current->next->grade < grade)
        {
            current = current->next;
        }
        newStudent->next = current->next;
        current->next = newStudent;

    }
    
}

int countStudent(student* head){
    int i = 0;
    student* temp = head;
    if (temp == NULL)
    return 0;
    while(temp != NULL){
        i++;
        temp = temp->next;
    }
    return i;
}
void showList (student* head){
    student* current = head;
    if (head == NULL)
        printf("NULL");
    else{    
    while(current != NULL){
        printf("%d/%f -->",current->id, current->grade);
        current = current->next;
    }
    printf("NULL.\n");
    }
}

float calculateAverage(student* head){
    student* current = head;
    if (head == NULL) return 0.0;
    float sum = 0.0;
    int count = 0;
    while (current != NULL){
        sum += current-> grade;
        count++;
        current = current->next;
    }
    return count ? sum / count : 0.0;
}

int main() {
    
    student* studentList = NULL;
    int numStudent;
    printf("enter the number of students: ");
    scanf("%d", &numStudent);
    initializeList(&studentList, numStudent);
    removeInitializations(&studentList);

    printf("initial list of students (empty): \n");
    showList(studentList);
    printf("number of students: %d\n", numStudent);

    int id;
    float grade;
    for (int i = 0; i < numStudent; i++)
    {
        printf("enter the student ID and grade: ");
        scanf("%d %f", &id, &grade);
        addStudentSorted(&studentList, id, grade);
    }

    printf("List after adding students: \n");
    showList(studentList);
    printf("Number of students: \n", countStudent(studentList));

    printf("Enter the new student's ID and grade to add: \n");
    scanf("%d %f", &id, &grade);
    addStudentSorted(&studentList, id, grade);
    
    printf("New list after adding a new student: \n");
    showList(studentList);
    printf("New number of students: %d\n", countStudent(studentList));
    
    printf("The average of the class grades: %.2f\n", calculateAverage(studentList));

    return 0;
}