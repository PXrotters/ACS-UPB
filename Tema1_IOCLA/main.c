#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void get_operations(void **operations);

int main(int argc, char const *argv[])
{
	const char *file = argv[1];
	FILE *f = fopen(file, "rb");
	if (f == NULL) {
		printf("Nu s-a putut deschide fisierul %s\n", file);
		return 1;
	}
	int i, j, ok = 0, index;
	int *nr_senzori = (int *)malloc(sizeof(int));
	int *tip_s = (int *)malloc(sizeof(int));
	int *date_int = (int *)malloc(sizeof(int));
	float *date_float = (float *)malloc(sizeof(float));
	int *nr_operatii = (int *)malloc(sizeof(int));
	char s[10];
	void **ops = malloc(sizeof(void *) * 8);
	size_t size = sizeof(int);
	get_operations(ops);
	fread (nr_senzori, sizeof(int), 1, f);  //citire numar de senzori
	sensor *Senzori = (sensor *)malloc((*nr_senzori) * sizeof(sensor));
	for (i = 0; i < (*nr_senzori); i++) {
		fread (tip_s, sizeof(int), 1, f);
		if ((*tip_s) == 0) {  //tip Tire_Sensor
			Senzori[i].sensor_type = TIRE;  //retinem tipul senzorului
			tire_sensor *data_ts = malloc(sizeof(*data_ts));
			fread (date_float, sizeof(float), 1, f);  //citim presiunea
			data_ts->pressure = (*date_float);
			fread (date_float, sizeof(float), 1, f);  //citim temperatura
			data_ts->temperature = (*date_float);
			fread (date_int, sizeof(int), 1, f);  //citim nivelul de uzura
			data_ts->wear_level = (*date_int);
			fread (date_int, sizeof(int), 1, f);  //citim scorul
			data_ts->performace_score = (*date_int);
			Senzori[i].sensor_data = data_ts;  //retinem datele senzorului tire
		} else {
			if ((*tip_s) == 1) {  //tip PMU
			Senzori[i].sensor_type = PMU;  //retinem tipul senzorului
			power_management_unit *pmu_data ;
			pmu_data = malloc(sizeof(*pmu_data));
			fread (date_float, sizeof(float), 1, f);  //citim voltajul
			pmu_data->voltage = (*date_float);
			fread (date_float, sizeof(float), 1, f);  //citim curentul
			pmu_data->current = (*date_float);
			fread (date_float, sizeof(float), 1, f);  //citim consumul
			pmu_data->power_consumption = (*date_float);
			fread (date_int, sizeof(int), 1, f);  //citim regenerarea de energie
			pmu_data->energy_regen = (*date_int);
			fread (date_int, sizeof(int), 1, f);  //citim stocarea de energie
			pmu_data->energy_storage = (*date_int);
			Senzori[i].sensor_data = pmu_data;
			}
		}
		fread(nr_operatii, sizeof(int), 1, f);  //citim numarul de operatii
		Senzori[i].nr_operations = (*nr_operatii);
		Senzori[i].operations_idxs = (int *)malloc((*nr_operatii) * size);
		for (j = 0; j < (*nr_operatii); j++) {
			fread(date_int, sizeof(int), 1, f);  //citire operatii
			Senzori[i].operations_idxs[j] = (*date_int);
		}
	}
	for (i = 0; i < (*nr_senzori) - 1; i++) {  //ordonam vectorul
		for (j = 0; j < (*nr_senzori) - i - 1; j++) {
			if (Senzori[j].sensor_type == TIRE) {
				if (Senzori[j + 1].sensor_type == PMU) {
					sensor aux;
					memcpy(&aux, &Senzori[j], sizeof (sensor));
					memcpy(&Senzori[j], &Senzori[j + 1], sizeof(sensor));
					memcpy(&Senzori[j + 1], &aux, sizeof(sensor));
				}
			}
		}
	}
	while (ok == 0) {
		scanf("%s", s);  //citire de la tastatura a comenzii
		if (strcmp(s, "print") == 0) {
			scanf ("%d", &index);  //citire de la tastatura a indexului
			if (index < 0 || index > (*nr_senzori)) {
				printf("Index not in range!\n");
			} else {
				if (Senzori[index].sensor_type == TIRE) {
					tire_sensor *data_ts;  //afisare senzori TIRE
					data_ts = Senzori[index].sensor_data;
					printf("Tire Sensor\n");
					printf("Pressure: %.2f\n", data_ts->pressure);
					printf("Temperature: %.2f\n", data_ts->temperature);
					printf("Wear Level: %d%%\n", data_ts->wear_level);
					if (data_ts->performace_score == 0) {
						printf("Performance Score: Not Calculated\n");
					} else {
						printf("Performance Score: ");
						printf("%d\n", data_ts->performace_score);
					}
				} else {
					if (Senzori[index].sensor_type == PMU) {
						power_management_unit *data_pmu;  //afisare senzori PMU
						data_pmu = Senzori[index].sensor_data;
						printf("Power Management Unit\n");
						printf("Voltage: %.2f\n", data_pmu->voltage);
						printf("Current: %.2f\n", data_pmu->current);
						printf("Power Consumption: ");
						printf("%.2f\n", data_pmu->power_consumption);
						printf("Energy Regen: %d%%\n", data_pmu->energy_regen);
						printf("Energy Storage: ");
						printf("%d%%\n", data_pmu->energy_storage);
					}
				}
			}
		}
		if (strcmp(s, "analyze") == 0) {
			scanf("%d", &index);
			if (index < 0 || index > (*nr_senzori)) {
				printf("Index not in range!\n");
			} else {
				for (i = 0; i < Senzori[index].nr_operations; i++) {
					int op_idx = Senzori[index].operations_idxs[i];
					((void (*)(void *))ops[op_idx])(Senzori[index].sensor_data);
				}
			}
			}
			if (strcmp(s, "clear") == 0) {
				for (i = 0; i < (*nr_senzori) ; i++) {
					if (Senzori[i].sensor_type == TIRE) {
						tire_sensor *data_ts;
						data_ts = Senzori[i].sensor_data;
						if (data_ts->pressure < 19 || data_ts->pressure > 28) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(data_ts);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							data_ts = NULL;
							i--;
						}
						if (data_ts != NULL && data_ts->temperature < 0) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(data_ts);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							data_ts = NULL;
							i--;
						}
						if (data_ts != NULL && data_ts->temperature > 120) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(data_ts);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							data_ts = NULL;
							i--;
						}
						if (data_ts != NULL && data_ts->wear_level < 0) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(data_ts);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							data_ts = NULL;
							i--;
						}
						if (data_ts != NULL && data_ts->wear_level > 100) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(data_ts);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							data_ts = NULL;
							i--;
						}
					}
					if (Senzori[i].sensor_type == PMU) {
						power_management_unit *pmu_data;
						pmu_data = Senzori[i].sensor_data;
						if (pmu_data->voltage < 10 || pmu_data->voltage > 20) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(pmu_data);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							pmu_data = NULL;
							i--;
						}
						if (pmu_data != NULL && pmu_data->current < -100) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(pmu_data);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							pmu_data = NULL;
							i--;
						}
						if (pmu_data != NULL && pmu_data->current > 100) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(pmu_data);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							pmu_data = NULL;
							i--;
						}
						if (pmu_data != NULL && pmu_data->power_consumption < 0) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(pmu_data);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							pmu_data = NULL;
							i--;
						}
						if (pmu_data != NULL && pmu_data->power_consumption > 1000) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(pmu_data);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							pmu_data = NULL;
							i--;
						}
						if (pmu_data != NULL && pmu_data->energy_regen < 0) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(pmu_data);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							pmu_data = NULL;
							i--;
						}
						if (pmu_data != NULL && pmu_data->energy_regen > 100) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(pmu_data);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							pmu_data = NULL;
							i--;
						}
						if (pmu_data != NULL && pmu_data->energy_storage < 0) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(pmu_data);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							pmu_data = NULL;
							i--;
						}
						if (pmu_data != NULL && pmu_data->energy_storage > 100) {
							for (j = i; j < (*nr_senzori) - 1; j++) {
								free(pmu_data);
								Senzori[j] = Senzori[j + 1];
							}
							free(Senzori[*nr_senzori].sensor_data);
							Senzori[*nr_senzori].sensor_data = NULL;
							(*nr_senzori)--;
							pmu_data = NULL;
							i--;
						}
					}
				}
			}
			if (strcmp(s, "exit") == 0) {
				ok++;
				break;
			}
		}
	for (i = 0; i < (*nr_senzori); i++) {  //eliberare memorie
		if (Senzori[i].sensor_type == TIRE) {
			tire_sensor *data_ts;
			data_ts = Senzori[i].sensor_data;
			free(data_ts);
		} else {
			power_management_unit *pmu_data;
			pmu_data = Senzori[i].sensor_data;
			free(pmu_data);
		}
		free(Senzori[i].operations_idxs);
	}
	free(ops);
	free(Senzori);
	free(nr_senzori);
	free(tip_s);
	free(date_float);
	free(date_int);
	free(nr_operatii);
	fclose(f);
	return 0;
}
