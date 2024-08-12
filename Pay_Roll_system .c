//pay rolling system
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int eno;           // Employee Number
    char ename[50];    // Employee Name
    float bp;          // Basic Pay
    float hra;         // House Rent Allowance
    float da;          // Dearness Allowance
    float pf;          // Provident Fund
    float gs;          // Gross Salary
    float ns;          // Net Salary
    int twd;           // Total Working Days
    int ndp;           // Number of Days Present
    float epay;        // Effected Pay
} Employee;

void writeEmployee()
 {
    FILE *fp = fopen("employee.dat", "ab");
    if (!fp)
    {
        printf("Error opening file");
        return;
    }
    Employee e;
    printf("Enter Employee Number: ");
    scanf("%d", &e.eno);

    getchar(); // Consume newline
    printf("Enter Employee Name: ");
    fgets(e.ename, sizeof(e.ename), stdin);
    e.ename[strcspn(e.ename, "\n")] = 0; // Remove newline

    printf("Enter Basic Pay: ");
    scanf("%f", &e.bp);

    printf("Enter Total Working Days: ");
    scanf("%d", &e.twd);

    printf("Enter Number of Days Present: ");
    scanf("%d", &e.ndp);

    e.hra = 0.20 * e.bp;
    e.da = 0.30 * e.bp;
    e.pf = 0.12 * e.bp;

    e.epay = (e.bp * ((float)e.ndp / e.twd));
    e.gs = e.epay + e.hra + e.da;
    e.ns = e.gs - e.pf;

    fwrite(&e, sizeof(Employee), 1, fp);
    fclose(fp);
}

void readEmployees()
 {
    FILE *fp = fopen("employee.dat", "rb");
    if (!fp)
    {
        printf("Error opening file");
        return;
    }
    Employee e;
    while (fread(&e, sizeof(Employee), 1, fp))
    {
        printf("\nEmployee Number: %d\n", e.eno);
        printf("Employee Name: %s\n", e.ename);
        printf("Basic Pay: %.2f\n", e.bp);
        printf("House Rent Allowance: %.2f\n", e.hra);
        printf("Dearness Allowance: %.2f\n", e.da);
        printf("Effected Pay: %.2f\n", e.epay);
        //printf("Provident Fund: %.2f\n", e.pf);
        printf("Gross Salary: %.2f\n", e.gs);
        printf("Provident Fund: %.2f\n", e.pf);
        printf("Net Salary: %.2f\n", e.ns);
    }
    fclose(fp);
}

void searchEmployee()
{
    FILE *fp = fopen("employee.dat", "rb");
    if (!fp)
    {
        printf("Error opening file");
        return;
    }
    int eno;
    printf("Enter Employee Number to Search: ");
    scanf("%d", &eno);
    Employee e;
    while (fread(&e, sizeof(Employee), 1, fp))
    {
        if (e.eno == eno)
        {
            printf("\nEmployee Number: %d\n", e.eno);
            printf("Employee Name: %s\n", e.ename);
            printf("Basic Pay: %.2f\n", e.bp);
            printf("House Rent Allowance: %.2f\n", e.hra);
            printf("Dearness Allowance: %.2f\n", e.da);
            printf("Provident Fund: %.2f\n", e.pf);
            printf("Effected Pay: %.2f\n", e.epay);
            printf("Gross Salary: %.2f\n", e.gs);
            printf("Net Salary: %.2f\n", e.ns);
            fclose(fp);
            return;
        }
    }
    printf("Employee number %d is not found.\n", eno);
    fclose(fp);
}

void deleteEmployee()
{
    FILE *fp = fopen("employee.dat", "rb");
    if (!fp)
    {
        perror("Error opening file");
        return;
    }
    FILE *temp = fopen("tempfile.dat", "wb");
    if (!temp)
    {
        perror("Error opening temporary file");
        fclose(fp);
        return;
    }
    int eno;
    printf("Enter Employee Number to Delete: ");
    scanf("%d", &eno);
    Employee e;
    int found = 0;
    while (fread(&e, sizeof(Employee), 1, fp))
    {
        if (e.eno == eno)
        {
            found = 1;
        }
        else
        {
            fwrite(&e, sizeof(Employee), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("employee.dat");
    rename("tempfile.dat", "employee.dat");
    if (found)
    {
        printf("Employee number %d is deleted successfully.\n", eno);
    }
    else
    {
        printf("Employee number %d is not found.\n", eno);
    }
}

int main()
 {
    int choice;
    while (1)
    {
        printf("\n-------- Main Menu --------\n");
        printf("1. Write Employee\n");
        printf("2. Read Employees\n");
        printf("3. Search Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                writeEmployee();
                break;
            case 2:
                readEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
