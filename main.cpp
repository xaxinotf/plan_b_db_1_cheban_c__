#pragma once

#include <iostream>
#include "master.h"
#include "slave.h"

using namespace std;

int unsupported_operation() {
    cout << "This operation is not supported." << endl;
}

int get_master() {
    struct master m;
    int id;
    cout << "Id:" << endl;
    cin >> id;
    m.id = id;
    if(get_m(&m, id) == 0) {
        cout << "Name: " << m.name << " Id: " << m.id << endl;
    }
    else {
        cout << "Error occurred during the get operation" << endl;
    }
    return 0;
}

int insert_master(){
    struct master m;

    cout << "Name:" << endl;
    cin >> m.name;
    if (insert_m(&m) == 0) {
        cout << "Master created."<< endl <<  "Name: " << m.name << endl << "Id: " << m.id << endl;
    }
    else {
        cout << "Error occurred during the insert operation" << endl;
    }
    return 0;
}


int update_master()
{
    struct master m;

    cout << "Id:" << endl;
    cin >> m.id;
    cout << "Name:" << endl;
    cin >> m.name;
    if(update_m(&m) == 0) {
        cout << "Master updated. Name: " << m.name << " Id: " << m.id << endl;
    }
    else {
        cout << "Error occurred during the update operation" << endl;
    }

    return 0;
}

int delete_master() {
    int id;
    cout << "Id:" << endl;
    cin >> id;

    if(del_m(id) == 0){
        cout << "Master deleted." << endl;
    }
    else {
        cout << "Error" << endl;
    }

    return 0;
}

int calc_master()
{
    int result = calc_m();
    if(calc_m() == -1){
        cout << "No master was inserted or error occurred." << endl;
        return 1;
    }
    cout << "Number of masters: " << result << endl;

    return 0;
}

int ut_master(){
    ut_m();
}

int get_slave() {
    struct slave s;
    int id;
    cout << "Id:" << endl;
    cin >> id;
    s.id = id;
    if(get_s(&s, id) == 0) {
        cout << "Name: " << s.name << " Id: " << s.id << " Master: " << s.m_id <<  endl;
    }
    else {
        cout << "Error occurred during the get operation" << endl;
    }
}

int insert_slave(){
    struct slave s;

    cout << "Name:" << endl;
    cin >> s.name;
    cout << "MasterID:" << endl;
    cin >> s.m_id;
    int result_code = insert_s(&s);
    if(result_code == 1) {
        cout << "Error occurred during the insert operation" << endl;
        return 1;
    }
    if(result_code == 2) {
        cout << "Error: Master with this id is not exsist" << endl;
        return 1;
    }
    if (result_code == 0) {
        cout << "Slave created."<< endl <<  "Name: " << s.name << endl << "Id: " << s.id << " Master: " << s.m_id <<  endl;
    }
}


int update_slave()
{
    struct slave s;

    cout << "Id:" << endl;
    cin >> s.id;
    cout << "Name:" << endl;
    cin >> s.name;
    cout << "MasterID:" << endl;
    cin >> s.m_id;
    int result_code = update_s(&s);
    if(result_code == 1) {
        cout << "Error occurred during the update operation" << endl;
        return 1;
    }
    if(result_code == 2) {
        cout << "Error: Master with this id is not exsist" << endl;
        return 1;
    }
    if (result_code == 0) {
        cout << "Slave updated." << endl << "Name: " << s.name << endl << "Id: " << s.id << " Master: " << s.m_id
             << endl;
    }
}

int delete_slave(){
    struct slave s;
    int id;
    cout << "Id:" << endl;
    cin >> id;
    s.id = id;

    if(del_s(id) == 0){
        cout << "Slave deleted." << endl;
    } else{
        cout << "Error" << endl;
    }
}

int calc_slave()
{
    int slaves = calc_s();
    if(slaves == -1){
        cout << "Error occurred." << endl;
    } else{
        cout << "Amount of slaves: " << slaves << endl;
    }
}

int ut_slave(){
    ut_s();
}

int display_options() {
    printf("Choose option:\n"
           "0 - Quit\n"
           "1 - Insert Master\n"
           "2 - Get Master\n"
           "3 - Update Master\n"
           "4 - Delete Master\n"
           "5 - Calc Masters\n"
           "6 - UT-Master\n"
           "7 - Insert Slave\n"
           "8 - Get Slave\n"
           "9 - Update Slave\n"
           "10 - Delete Slave\n"
           "11 - UT-Slave\n"
           "12 - Calc Slaves\n"
    );

}

int init_db() {
    FILE *fp;
    if ((fp = fopen(MASTER_DATA, "r")) == NULL)
    {
        fclose(fp);
        fp = fopen(MASTER_DATA, "wb+");
        fwrite(0, 0, 1, fp);
        fclose(fp);
    }
    if ((fp = fopen(MASTER_IND, "r")) == NULL)
    {
        fclose(fp);
        fwrite(0, 0, 1, fp);
        fp = fopen(MASTER_IND, "wb+");
        fclose(fp);
    }
    if ((fp = fopen(SLAVE_DATA, "r")) == NULL)
    {
        fclose(fp);
        fp = fopen(SLAVE_DATA, "wb+");
        fwrite(0, 0, 1, fp);
        fclose(fp);
    }
    if ((fp = fopen(SLAVE_IND, "r")) == NULL)
    {
        fclose(fp);
        fwrite(0, 0, 1, fp);
        fp = fopen(SLAVE_IND, "wb+");
        fclose(fp);
    }
}


int main() {
    init_db();
    struct offset o {};
    o.id = -1;
    if (get_offset_master() == -2)
        write_offset_master(&o);
    if (get_offset_slave() == -2)
        write_offset_slave(&o);
    int command_id;

    do {
        display_options();
        cin >> command_id;
        switch (command_id) {
            case 0:
                return 0;
            case 1:
                insert_master();
                break;
            case 2:
                get_master();
                break;
            case 3:
                update_master();
                break;
            case 4:
                delete_master();
                break;
            case 5:
                calc_master();
                break;
            case 6:
                ut_master();
                break;
            case 7:
                insert_slave();
                break;
            case 8:
                get_slave();
                break;
            case 9:
                update_slave();
                break;
            case 10:
                delete_slave();
                break;
            case 11:
                ut_slave();
                break;
            case 12:
                calc_slave();
                break;
            default:
                unsupported_operation();
                break;
        }
        cout << endl;
    } while(1);
}


