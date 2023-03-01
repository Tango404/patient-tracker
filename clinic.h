#ifndef CLINIC_H
#define CLINIC_H


//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

// !!! DO NOT MODIFY THESE MACRO'S !!!
#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10


// Additional macro's:
#define TRUE 0
#define FALSE 1
#define START_HOUR 10
#define END_HOUR 14
#define MINUTE_INTERVAL 30


//////////////////////////////////////
// Structures
//////////////////////////////////////
struct Phone
{
    char description[PHONE_DESC_LEN+1];
    char number[PHONE_LEN+1];

};

struct Patient
{
    int patientNumber;
    char name[NAME_LEN];
    struct Phone phone;
};

struct Time
{
    int hour;
    int min;

};

struct Date
{
    int year;
    int month;
    int day;


};

struct Appointment
{
    int patientNum;
    struct Time time;
    struct Date date;
};


// !!! DO NOT MODIFY THIS DATA TYPE !!!
struct ClinicData
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void);

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt);

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField);


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct ClinicData* data);

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient);

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data);

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);

// View ALL scheduled appointments
void viewAllAppointments (struct ClinicData *data);

// View appointment schedule for the user input date
void viewAppointmentSchedule (struct ClinicData *data);

// Add an appointment record to the appointment array
void addAppointment (struct Appointment *appointments, int maxAppointments, struct Patient *patients, int maxPatient);

// Remove an appointment record from the appointment array
void removeAppointment (struct Appointment *appointments, int maxAppointments, struct Patient *patients, int maxPatient);



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max);

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max);

// Bubble sorts appointments by year, month, day, hour, and minute
void sortAppointments (struct Appointment *appointments, int max);

// Finds appointment based on the date and time, returns the index of the matched appointment
int findAppointment (struct Appointment appointment[], int patientNumber, int year, int month, int day, int maxAppointments);

// Finds an empty appointment in the appointment struct array, and returns the index
int findEmptyAppointment (struct Appointment *appointments, int maxAppointments);

// Finds the number of BOOKED appointments out of the max number of appointments
int numberOfAppointments (struct Appointment *appointments, int maxAppointments, int *returnValue);

// Calculates number of days by using the month and year (accounts for leap year)
void setDay (int *dayPTR, int year, int month);



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient);

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone);

// Used to input appointment information when adding an appointment, returns a number if setting the data was successful
int inputAppointment (struct Appointment *appointment);



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max);

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max);


#endif // !CLINIC_H