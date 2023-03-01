#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient, const struct Appointment* appoint, int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
            case 0:
                printf("Are you sure you want to exit? (y|n): ");
                selection = !(inputCharOption("yn") == 'y');
                putchar('\n');
                if (!selection)
                {
                    printf("Exiting system... Goodbye.\n\n");
                }
                break;
            case 1:
                menuPatient(data->patients, data->maxPatient);
                break;
            case 2:
                menuAppointment(data);
                break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
            case 1:
                displayAllPatients(patient, max, FMT_TABLE);
                suspend();
                break;
            case 2:
                searchPatientData(patient, max);
                break;
            case 3:
                addPatient(patient, max);
                suspend();
                break;
            case 4:
                editPatient(patient, max);
                break;
            case 5:
                removePatient(patient, max);
                suspend();
                break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN, 0);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("\nPatient record updated!\n\n");
        }

    } while (selection);
}


// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
            case 1:
                viewAllAppointments(data);
                suspend();
                break;
            case 2:
                viewAppointmentSchedule(data);
                suspend();
                break;
            case 3:
                addAppointment(data->appointments, data->maxAppointments,
                               data->patients, data->maxPatient);  // ToDo: You will need to create this function!
                suspend();
                break;
            case 4:
                removeAppointment(data->appointments, data->maxAppointments,
                                  data->patients, data->maxPatient);  // ToDo: You will need to create this function!
                suspend();
                break;
        }
    } while (selection);
}

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    int patients = 0;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
        for (i = 0; i < max; i++)
        {
            if(patient[i].patientNumber != 0)
            {
                displayPatientData(&patient[i], fmt);
                patients++;
            }
        }
    }
    else if (fmt == FMT_FORM)
    {
        for (i = 0; i < max; i++)
        {
            if(patient[i].patientNumber != 0)
            {
                displayPatientData(&patient[i], fmt);
                patients++;
            }
        }
    }

    if (patients == 0)
    {
        printf("\n*** No records found ***\n");
    }

    printf("\n");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection = 0;

    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);

        switch (selection)
        {
            case 1:
                putchar('\n');
                searchPatientByPatientNumber(patient, max);
                suspend();
                break;
            case 2:
                searchPatientByPhoneNumber(patient, max);
                suspend();
                break;
            default:
                putchar('\n');
                break;
        }

    } while (selection);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i = 0;
    int flag = 0;
    int index = 0;
    int notFound = 0;

    notFound = 0;

    while(flag == 0)
    {
        if (i >= max)
        {
            notFound = 1;
            flag = 1;
        }
        else if(patient[i].patientNumber == 0000)
        {
            index = i;
            flag = 1;
        }
        i++;
    };

    if(notFound == 1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("\n*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int index;
    int patientNumber;
    printf("Enter the patient number: ");
    patientNumber = inputInt();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (index >= 0)
    {
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n");
    }

}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    const int FMT = FMT_FORM;
    int patientNumber = 0;
    int recordExists = 0;
    char confirmation;
    const struct Patient EmptyState = {0};

    printf("Enter the patient number: ");
    patientNumber = inputInt();
    putchar('\n');

    recordExists = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (recordExists >= 0)
    {
        displayPatientData(&patient[recordExists], FMT);

        putchar('\n');

        printf("Are you sure you want to remove this patient record? (y/n): ");
        confirmation = inputCharOption("yn");

        if(confirmation == 'n')
        {
            printf("Operation aborted.\n\n");
        }
        else
        {
            patient[recordExists] = EmptyState;

            printf("Patient record has been removed!\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i = 0;
    int j = 0;
    int isAllRecords = 1;
    int includeDateField = 1;

    sortAppointments(data->appointments, data->maxPatient);

    displayScheduleTableHeader(&data->appointments->date, isAllRecords);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].patientNum == data->patients[j].patientNumber)
            {
                displayScheduleData(&data->patients[j], &data->appointments[i], includeDateField);
            }
        }
    }

    putchar('\n');

}

// View appointment schedule for the user input date
void viewAppointmentSchedule (struct ClinicData *data)
{

    // Loop Vars
    int i;
    int j;
    int counter = 0;

    // Temp Struct
    struct Appointment temp;

    // Get user input for year
    printf("Year        : ");
    temp.date.year = inputIntPositive();

    // Get user input for month
    printf("Month (1-12): ");
    temp.date.month = inputIntRange(1, 12);

    // Calculates and gets user input for day
    setDay(&temp.date.day, temp.date.year, temp.date.month);

    putchar('\n');

    displayScheduleTableHeader(&temp.date, TRUE);

    sortAppointments(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].patientNum == data->patients[j].patientNumber)
            {
                if (data->appointments[i].date.year == temp.date.year && data->appointments[i].date.month == temp.date.month && data->appointments[i].date.day == temp.date.day)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], TRUE);
                    counter++;
                }
            }
        }
    }

    if (counter == 0)
    {
        printf("\n*** No records found ***\n");
    }

    putchar('\n');

}

// Add an appointment record to the appointment array
void addAppointment (struct Appointment *appointments, int maxAppointments, struct Patient *patients, int maxPatient)
{
    // Loop Vars
    int flag = 0;
    int i;

    // Used to get the return value from function
    int appointmentInputted;

    // Vars used to calculate the empty index of the struct arrays
    int patientIndex = -1;
    int appointmentIndex = -1;

    // Used to recieve the number of appointments
    int numAppointments = 0;

    // Struct used to recieve data, gets assigned later.
    struct Appointment added;

    // Calculating number of filled appointments, and find empty position
    numberOfAppointments(appointments, maxAppointments, &numAppointments);
    appointmentIndex = findEmptyAppointment(appointments, maxAppointments);

    if (numAppointments < maxAppointments && appointmentIndex >= 0)
    {

        do
        {
            printf("Patient Number: ");
            added.patientNum = inputIntPositive();
            patientIndex = findPatientIndexByPatientNum(added.patientNum, patients, maxPatient);

            if (patientIndex == -1)
            {
                printf("ERROR: Patient record not found!\n\n");
            }
            else
            {
                flag = 1;
            }

        } while (flag == 0);


        // Once the loop above gets terminated, the same flag variable is used in the condition.

        while (flag == 1)
        {
            // Function return's 1, once inputs have been completed
            appointmentInputted = inputAppointment(&added);

            if (appointmentInputted == 1)
            {
                for (i = 0; i < maxAppointments; i++)
                {

                    if (added.date.year == appointments[i].date.year &&
                        added.date.month == appointments[i].date.month &&
                        added.date.day == appointments[i].date.day &&
                        added.time.hour == appointments[i].time.hour &&
                        added.time.min == appointments[i].time.min)
                    {
                        printf("\nERROR: Appointment timeslot is not available!\n\n");
                        flag = 1;
                    }
                    else if (added.date.year != appointments[i].date.year &&
                             added.date.month != appointments[i].date.month &&
                             added.date.day != appointments[i].date.day &&
                             added.time.hour != appointments[i].time.hour &&
                             added.time.min != appointments[i].time.min)
                    {
                        flag = 0;
                    }
                }
            }
        }

        // Using the same flag variable, if the above else if condition is true the loop is terminated by setting flag to zero.
        // This conditon now checks the flag variable and assigns the appointment index to the temporary input struct.

        if (flag == 0)
        {
            appointments[appointmentIndex] = added;
            printf("\n*** Appointment scheduled! ***\n\n");
        }
    }
    else
    {
        printf("\nERROR: Appointments are full, please contact us to book an appointment!\n");
    }

    clearInputBuffer();

}

// Remove an appointment record from the appointment array
void removeAppointment (struct Appointment *appointments, int maxAppointments, struct Patient *patients, int maxPatient)
{
    // Loop Vars
    int patientIndex = -1;
    int index = -1;

    // Used to get the return value from function
    int year = 0;
    int month = 0;
    int day = 0;
    int patientNumber = 0;
    char selection;

    // Empty struct used to set to zero
    struct Appointment empty = {0};

        printf("Patient Number: ");
        scanf("%d", &patientNumber);

        patientIndex = findPatientIndexByPatientNum(patientNumber, patients, maxPatient);

        if (patientIndex > -1)
        {
            // Get user input for year
            printf("Year        : ");
            year = inputIntPositive();

            // Get user input for month
            printf("Month (1-12): ");
            month = inputIntRange(1, 12);

            // Calculates and gets user input for day
            setDay(&day, year, month);

            putchar('\n');

            // Display the patient's data
            displayPatientData(&patients[patientIndex], FALSE);

            // Iterates through appointment struct array to find the appointment, and saves appointment in index
            index = findAppointment(appointments, patientNumber, year, month, day, maxAppointments);


            if (index != -1)
            {
                printf("Are you sure you want to remove this appointment (y,n): ");
                selection = inputCharOption("yn");

                if (selection == 'y' || selection == 'Y')
                {
                    appointments[index] = empty;
                    printf("\nAppointment record has been removed!\n\n");
                }
                else
                {
                    printf("\n*** Operation Aborted! ***\n\n");
                }
            }
            else
            {
                printf("\n*** No Appointments with that date! ***\n\n");
            }
        }
        else
        {
            printf("ERROR: Patient record not found!\n\n");
            clearInputBuffer();
        }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    const int FMT = FMT_FORM;
    int patientNumber = 0;
    int value = 0;

    printf("Search by patient number: ");
    patientNumber = inputInt();

    value = findPatientIndexByPatientNum(patientNumber, patient, max);

    if(value >= 0)
    {
        putchar('\n');
        displayPatientData(&patient[value], FMT);
        putchar('\n');
    }
    else
    {
        printf("\n*** No records found ***\n\n");
    }
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    const int FMT = FMT_TABLE;
    char phoneNumber[PHONE_LEN + 1]; // +1 is to accommodate for the NULL terminator
    int i;
    int found;

    printf("\nSearch by phone number: ");
    inputCString(phoneNumber, 10, 10, 0); // Only accepts up till 10 chars for the number.

    putchar('\n');

    displayPatientTableHeader();

    found = 0; // Resets found counter

    for (i = 0; i < max; i++)
    {
        if(strcmp(patient[i].phone.number, phoneNumber) == 0) // Compares index'd struct's phone number to entered phone number.
        {
            displayPatientData(&patient[i], FMT);
            found++;
        }
    }
    putchar('\n');

    if(found == 0)
    {
        printf("*** No records found ***\n\n");
    }
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int biggest = patient[0].patientNumber;

    for (i = 0; i < max; i++)
    {
        if(patient[i].patientNumber > biggest)
        {
            biggest = patient[i].patientNumber;
        }
    }

    biggest += 1;

    return biggest;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i;
    int found = 0;
    int counter;

    counter = 0;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            found = i;
            counter++;
        }
    }

    if (counter == 0)
    {
        found = -1;
    }

    return found;
}

// Bubble sorts appointments by year, month, day, hour, and minute
void sortAppointments (struct Appointment *appointments, int max)
{
    int i;
    int j;
    struct Appointment temp;

    for (i = 0; i < max - 1; i++)
    {
        for (j = i+1; j < max - 1; j++)
        {
            if (appointments[i].date.year != 0000 && appointments[j].date.year != 0000)
            {
                if (appointments[i].date.year > appointments[j].date.year)
                {
                    temp = appointments[i];
                    appointments[i] = appointments[j];
                    appointments[j] = temp;
                }
                else if (appointments[i].date.year == appointments[j].date.year)
                {
                    if (appointments[i].date.month > appointments[j].date.month)
                    {
                        temp = appointments[i];
                        appointments[i] = appointments[j];
                        appointments[j] = temp;
                    }
                    else if (appointments[i].date.month == appointments[j].date.month)
                    {
                        if (appointments[i].date.day > appointments[j].date.day)
                        {
                            temp = appointments[i];
                            appointments[i] = appointments[j];
                            appointments[j] = temp;
                        }
                        else if (appointments[i].date.day == appointments[j].date.day)
                        {
                            if (appointments[i].time.hour > appointments[j].time.hour)
                            {
                                temp = appointments[i];
                                appointments[i] = appointments[j];
                                appointments[j] = temp;
                            }
                            else if (appointments[i].time.hour == appointments[j].time.hour)
                            {
                                if (appointments[i].time.min > appointments[j].time.min)
                                {
                                    temp = appointments[i];
                                    appointments[i] = appointments[j];
                                    appointments[j] = temp;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Calculates number of days by using the month and year (accounts for leap year)
void setDay (int *dayPTR, int year, int month)
{
    int minDayBound = 1;
    int maxDayBound = 0;
    int dayEntered;

    if (month == 2)
    {
        if ( ((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0)
        {
            maxDayBound = 29;
        }
        else
        {
            maxDayBound = 28;
        }
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        maxDayBound = 31;
    }
    else
    {
        maxDayBound = 30;
    }

    printf("Day (%d-%d)  : ", 1, maxDayBound);
    dayEntered = inputIntRange(minDayBound, maxDayBound);

    *dayPTR = dayEntered;

}

// Finds the number of BOOKED appointments out of the max number of appointments
int numberOfAppointments (struct Appointment *appointments, int maxAppointments, int *returnValue)
{
    int i;
    int returnNumber = 0;

    for (i = 0; i < maxAppointments; i++)
    {
        if (appointments[i].date.year != 0000)
        {
            returnNumber++;
        }
    }

    *returnValue = returnNumber;

    return *returnValue;
}

// Finds an empty appointment in the appointment struct array, and returns the index
int findEmptyAppointment (struct Appointment *appointments, int maxAppointments)
{
    int i;
    int index = -1;
    int flag = 0;

    for (i = 0, flag = 0; i < maxAppointments && flag == 0; i++)
    {
        if (appointments[i].date.year == 0 && appointments[i].date.month == 0 && appointments[i].date.day == 0 && appointments[i].time.hour == 0 && appointments[i].time.min == 0)
        {
            index = i;
            flag = 1;
        }
    }

    return index;
}

// Finds appointment based on the date and time, returns the index of the matched appointment
int findAppointment (struct Appointment appointment[], int patientNumber, int year, int month, int day, int maxAppointments)
{
    int flag = 0;
    int index = -1;
    int i = 0;

    do
    {
        if (patientNumber == appointment[i].patientNum && year == appointment[i].date.year && month == appointment[i].date.month && day == appointment[i].date.day)
        {
            index = i;
            flag = 1;
        }

        i++;

    } while (flag == 0 && i <= maxAppointments);

    return index;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input");
    putchar('\n');
    printf("------------------");
    putchar('\n');
    printf("Number: %05d", patient->patientNumber);
    putchar('\n');
    printf("Name  : ");
    inputCString(patient->name, 1, 15, 0);
    putchar('\n');
    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection;

    printf("Phone Information");
    putchar('\n');
    printf("-----------------");
    putchar('\n');
    printf("How will the patient like to be contacted?");
    putchar('\n');
    printf("1. Cell");
    putchar('\n');
    printf("2. Home");
    putchar('\n');
    printf("3. Work");
    putchar('\n');
    printf("4. TBD");
    putchar('\n');
    printf("Selection: ");
    selection = inputIntRange(1,4);

    switch (selection)
    {
        case 1:
            strcpy(phone->description, "CELL");
            putchar('\n');
            printf("Contact: %s", phone->description);
            putchar('\n');
            printf("Number : ");
            inputPhoneNumber(phone->number, PHONE_LEN);
            break;
        case 2:
            strcpy(phone->description, "HOME");
            putchar('\n');
            printf("Contact: %s", phone->description);
            putchar('\n');
            printf("Number : ");
            inputPhoneNumber(phone->number, PHONE_LEN);
            break;
        case 3:
            strcpy(phone->description, "WORK");
            putchar('\n');
            printf("Contact: %s", phone->description);
            putchar('\n');
            printf("Number : ");
            inputPhoneNumber(phone->number, PHONE_LEN);
            break;
        case 4:
            strcpy(phone->description, "TBD");
            *phone->number = '\0'; // Sets string to empty
            break;
        default:
            break;
    }
}

// Used to input appointment information when adding an appointment, returns a number if setting the data was successful
int inputAppointment (struct Appointment *appointment)
{
    int flag = 0;

    printf("Year        : ");
    scanf("%d", &appointment->date.year);

    printf("Month (1-12): ");
    scanf("%d", &appointment->date.month);

    setDay(&appointment->date.day, appointment->date.year, appointment->date.month);

    do
    {
        printf("Hour (0-23)  : ");
        scanf("%d", &appointment->time.hour);

        printf("Minute (0-59): ");
        scanf("%d", &appointment->time.min);

        flag = 0;

        if ((appointment->time.hour > END_HOUR || appointment->time.hour < START_HOUR) || (appointment->time.hour == END_HOUR && appointment->time.min == MINUTE_INTERVAL) || (appointment->time.min != 0 && appointment->time.min != MINUTE_INTERVAL) )
        {
            printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);
        }
        else
        {
            flag = 1;
        }

    } while (flag == 0);

    return flag;

}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;

    FILE *fp = NULL;

    fp = fopen(datafile, "r");

    i = 0;

    if (fp != NULL)
    {
        while (i < max && !feof(fp))
        {
            fscanf(fp, "%d|%14[^|]|%4[^|]|%10[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number);
            i++;
        };

        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("Error opening file, please try again!\n");
    }

    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;
    FILE *fp = NULL;

    fp = fopen(datafile, "r");

    i = 0;

    if (fp != NULL)
    {
        while (i < max && !feof(fp))
        {
            fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNum, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min);
            i++;
        }

        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("Error opening file, please try again!\n");
    }

    sortAppointments(appoints, max);

    return i;
}