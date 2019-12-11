#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <gdbm.h>
#define GDBMFILE "gdbm_test“
#define TABLESIZE 50 
struct info {
char name[20]; 
int age; 
}; 
int main( int argc, char *argv[])
{
struct info infotable;
int id, i = 0;
GDBM_FILE dbf;
datum key, data;
/* GDBM 파일 생성 */
dbf = gdbm_open(GDBMFILE, 2048, GDBM_WRCREAT, 00664, NULL);
if (dbfd == NULL) {
printf("gdbm_open failed, %s\n", gdbm_strerror(gdbm_errno)); 
exit(1);
} 
key.dptr = (char *)&id;
key.dsize = sizeof(int);
data.dptr = (char *)&infotable;
data.dsize = sizeof(struct info);
while (scanf("%d%s%d", &id, infotable.name, 
&(infotable.age)) != EOF && i++ < TABLESIZE) {
/* DB에 넣기 */
if (gdbm_store(dbf, key, data, GDBM_REPLACE) != 0) {
printf("gdbm_store failed to store key %d\n", id);
exit(1);
}
}
/* DB 탐색 */
while (scanf("%d", &id) != EOF) {
data = gdbm_fetch(dbf, key);
if (data.dptr != NULL) {
memcpy(&infotable, data.dptr, data.dsize); 
printf("found id=%d, name=%s, age=%d\n", id, infotable.name, infotable.age); 
} else { 
printf("no such employee of id %d\n", id); 
} 
} 
gdbm_close(dbf); 
}
