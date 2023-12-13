#include <iostream>
#include <algorithm>

using namespace std;


struct Process {
    int pid; 
    int bt;  
};

int main() {
    int select;
    int n = 0;
    int* processes = nullptr;
    int* burstTime = nullptr;
    Process* proc = nullptr;

    do {
        cout << "Menu:\n";
        cout << "1. Agregar valor\n";
        cout << "2. Calcular FCFS\n";
        cout << "3. Calcular SJF \n";
        cout << "4. Calcular RR\n";
        cout << "5. Salir \n";
        cout << "Selecciona una opcion: ";
        cin >> select;

        switch (select) {
            case 1: {
                cout << "Ingresa la cantidad de procesos: ";
                cin >> n;

                // Borra lo anterior agregado
                delete[] processes;
                delete[] burstTime;
                delete[] proc;

                processes = new int[n];
                burstTime = new int[n];
                proc = new Process[n];

                // Añade el burst time, tenemos en cuenta un Arrival time de 0
                for (int i = 0; i < n; ++i) {
                    cout << "Agrega el Burst time de procesos " << i + 1 << ": ";
                    cin >> burstTime[i];
                    processes[i] = i + 1; // Asigna los procesos

                    // Inicializa el arreglo proc
                    proc[i].pid = processes[i];
                    proc[i].bt = burstTime[i];
                }
                break;
            }

            case 2: {
                if (n > 0) {
                    // Calcula el tiempo promedio
                    int wt[n], tat[n], total_wt = 0, total_tat = 0;
                    wt[0] = 0;
                    for (int i = 1; i < n; i++) {
                        wt[i] = burstTime[i - 1] + wt[i - 1];
                    }

                    for (int i = 0; i < n; i++) {
                        tat[i] = burstTime[i] + wt[i];
                    }

                    // Muestra el resultado
                    cout << "Procesos  " << " Burst time  " << " Waiting time  " << " Turn around time\n";
                    for (int i = 0; i < n; i++) {
                        total_wt = total_wt + wt[i];
                        total_tat = total_tat + tat[i];
                        cout << "   " << processes[i] << "\t\t" << burstTime[i] << "\t    " << wt[i] << "\t\t  " << tat[i] << endl;
                    }

                    cout << "Promedio waiting time = " << (float)total_wt / (float)n << endl;
                    cout << "Promedio turn around time = " << (float)total_tat / (float)n << endl;
                } else {
                    cout << "Agrega valores.\n";
                }
                break;
            }

            case 3: {
                if (n > 0) {
                    // Hace un sort con los burst time
                    sort(proc, proc + n, [](const Process& a, const Process& b) {
                        return a.bt < b.bt;
                    });

                    // Calcula y muestra
                    int wt[n], tat[n], total_wt = 0, total_tat = 0;

                    wt[0] = 0;
                    for (int i = 1; i < n; i++) {
                        wt[i] = proc[i - 1].bt + wt[i - 1];
                    }

                    for (int i = 0; i < n; i++) {
                        tat[i] = proc[i].bt + wt[i];
                    }

                    // Muestra con todo detalle
                    cout << "\nProcesos " << " Burst time "
                         << " Waiting time " << " Turn around time\n";

                    // Calcula WT y TT
                    for (int i = 0; i < n; i++) {
                        total_wt = total_wt + wt[i];
                        total_tat = total_tat + tat[i];
                        cout << " " << proc[i].pid << "\t\t"
                             << proc[i].bt << "\t " << wt[i]
                             << "\t\t " << tat[i] << endl;
                    }

                    cout << "Promedio waiting time = "
                         << (float)total_wt / (float)n;
                    cout << "\nPromedio turn around time = "
                         << (float)total_tat / (float)n << endl;
                } else {
                    cout << "Ingresa valores de Burst time primero.\n";
                }
                break;
            }            case 4: {
                int quantum;
                cout << "Ingresa el quantum para Round Robin: ";
                cin >> quantum;

                if (n > 0) {
                    int wt[n] = {0}, tat[n] = {0}, rem_bt[n];

                    // Toma el burstTime 
                    for (int i = 0; i < n; i++)
                        rem_bt[i] = burstTime[i];

                    int t = 0; // El tiempo asumido en 0

                    // Bucle del round robin
                    while (true) {
                        bool done = true;

                        // Organiza en bucle
                        for (int i = 0; i < n; i++) {
                            if (rem_bt[i] > 0) {
                                done = false; // Procesos pendientes

                                if (rem_bt[i] > quantum) {
                                    t += quantum;

                                    // Resta valores al burstTime
                                    rem_bt[i] -= quantum;
                                } else {
                                    // Incrementa el valor del tiempo para ver los procesos
                                    t = t + rem_bt[i];

                                    // El tiempo de espera es el tiempo del momento menos el de proceso
                                    wt[i] = t - burstTime[i];

                                    // Cuando se finaliza
                                    rem_bt[i] = 0;
                                }
                            }
                        }

                        // Si finaliza da un quiebre
                        if (done)
                            break;
                    }

                    // Calcula el TT
                    for (int i = 0; i < n; i++)
                        tat[i] = burstTime[i] + wt[i];

                    // Muestra procesos con todo detalle
                    cout << "Procesos " << " Burst time " << " Waiting time " << " Turn around time\n";

                    // Calcula el total TT y WT
                    int total_wt = 0, total_tat = 0;
                    for (int i = 0; i < n; i++) {
                        total_wt += wt[i];
                        total_tat += tat[i];
                        cout << " " << processes[i] << "\t\t" << burstTime[i] << "\t " << wt[i] << "\t\t " << tat[i] << endl;
                    }

                    cout << "Promedio waiting time = " << (float)total_wt / (float)n << endl;
                    cout << "Promedio turn around time = " << (float)total_tat / (float)n << endl;
                } else {
                    cout << "Agrega valores.\n";
                }
                break;
            }

            default:
                cout << "Opcion invalida.\n";
                break;
        }

    } while (select != 5);

    // Borra memoria
    delete[] processes;
    delete[] burstTime;
    delete[] proc;
    return 0;
}
