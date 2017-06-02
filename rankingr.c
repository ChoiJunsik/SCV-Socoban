#include <stdio.h>

int main(void){
	FILE *rank;
	rank = fopen("ranking", "rt");

  int name[10] = {0};

  scanf("%s", &name);

  int stage = 0;

  scanf("%d", &stage);

	int gotrash;
	int trashforname[10] = {0};
	int record[5][6] = {0};
	int stage_amin;
	int name_amin[5][6][10] = {0};
	for (int k = 0; k < 5; k += 1){
		fscanf(rank, "===%d===\n", &stage_amin);
		for (int n = 0; n < 5; n += 1)
			fscanf(rank, "%s  -  %d\n", &name_amin[stage_amin][n], &record[stage_amin][n]);
	}
	for (int nm = 0; nm < 10; nm += 1)
		name_amin[stage][5][nm] = name[nm];
	record[stage][5] = 300;
  for (int n = 0; n < 6; n += 1)
    printf("%d.", record[stage][n]);
	//정렬할거야 ><
	for (int outplay = 0; outplay < 5; outplay += 1){
		for (int inplay = 0; inplay < 5 - outplay; inplay += 1){
			if (record[stage][inplay] > record[stage][inplay + 1]){
        printf("%d: [%d] ", record[stage][inplay], inplay);
				gotrash = record[stage][inplay];
				record[stage][inplay] = record[stage][inplay + 1];
				record[stage][inplay + 1] = gotrash;

				for (int nm = 0; nm < 10; nm += 1){
					trashforname[nm] = name_amin[stage][inplay][nm];
					name_amin[stage][inplay][nm] = name_amin[stage][inplay + 1][nm];
					name_amin[stage][inplay + 1][nm] = trashforname[nm];
				}

			}
		}}

	for (int k = 0; k < 5; k += 1){
		fprintf(rank, "===%d===\n", k);
		for (int n = 0; n < 5; n += 1)
			fprintf(rank, "%s  -  %d\n", name_amin[k][n], record[k][n]);
	}

	fclose(rank);


	return 0;

}
