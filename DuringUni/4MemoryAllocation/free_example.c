#include <stdio.h>

int main(){
	int *nums = NULL;

	nums = (int*)malloc(sizeof(int) * 10);
	for (int i = 0; i < 10; ++i){
		nums[i] = 9990 + i;
		printf("%d: %d\n",i,nums[i]);
	}

	free(nums);
	nums = NULL; //its best practice to set pointers to null after you are done, so you can see if you are accessing a section of memory that no longer exists

	// now this section will cause a segmentation fault because nums will point to nothing
	for (int i = 0; i < 10; ++i){
		printf("%d: %d\n",i,nums[i]);
	}

	return 0;

	// realloc() takes previously allocated memory, puts everything into a new size
}

// gcc mem1.c -o mem1 -g