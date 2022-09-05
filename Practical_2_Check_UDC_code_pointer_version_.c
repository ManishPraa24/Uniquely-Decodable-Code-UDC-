#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

// 190420116054
// Data Compression
// Practical 2: To check whether the entered code is UDC or not

int func_check = 0;

int check_danglings_in_prefix(char **dangling_suffix, char **code_char, int dang_count, int n){		//Function to check whether there exists..
	func_check++;																		//..such prefix same as dangling suffix
	int flag, i, j, k;
	
	for(i=0; i<dang_count; i++){					// It will return 1 if dangling_suffix is same as any of the code_word, else return 0
		
		for(j=0; j<n; j++){
			
			flag=0;
			
			for(k=0; *(*(dangling_suffix+i)+k)!='\n' && *(*(code_char+j)+k)!='\n'; k++){
				if(*(*(dangling_suffix+i)+k) != *(*(code_char+j)+k)){
					flag=1;
					break;
				}
			}
			
			if(flag==0){
				if(*(*(dangling_suffix+i)+k)=='\n' && *(*(code_char+j)+k)=='\n'){
					return 1;
				}
			}
			
		}
		
	}
	
	return 0;
	
}


int check_temp_in_dangling_suffix(char **dangling_suffix, char *temp_char, int dang_count){
	func_check++;										//Function to check if there exists such dangling suffix which is discovered already
	int i, j, flag = 0;
	for(i=0; i<dang_count; i++){
		
		j=0;																	// It will return 1, if temp_char is not in dangling_suffix array storage, else return 0
		flag = 0;
		while(*(*(dangling_suffix+i)+j)!='\n' && *(temp_char+j)!='\n' ){
			
			if(*(*(dangling_suffix+i)+j) != *(temp_char+j)){
				flag = 1;
				break;
			}
			
			j++;
		}
		
		if(flag==0){
			if(*(*(dangling_suffix+i)+j)=='\n' && *(temp_char+j)!='\n' && i==dang_count-1){
				return 1;
			}
			else if(*(*(dangling_suffix+i)+j)=='\n' && *(temp_char+j)=='\n'){
				return 0;
			}
		}
		/*else if(flag==1){
			if(*(temp_char + j + 1)=='\n'){
				return 1;
			}
		}  */
		
	}
	
	return 1;
	
}

int check_prefix(char **code_char, int n){
	func_check++;					//This function is to check whether the given set of codewords is prefix code or not
	int i, j, k, l, o, p;
	
	
	for(i=0; i<n-1; i++){					// It will return 1, if code_words are not prefix code, else return 0
		
		for(j=0; j<n; j++){
			
			if(j==i){
				continue;
			}
			
			k=0;
			l=0;
			p=0;
			
			for(k=0, l=0; *(*(code_char+i)+k)!='\n' && *(*(code_char+j)+l)!='\n'; ){
				
				if(*(*(code_char+i)+k) != *(*(code_char+j)+l)){
					p=1;	
					break;
				}
				else{
					k++; l++;
				}
				
			}
			
			if(p==0){
				return 1;
			}
			
		}
			
	}
	
	return 0;
	
}

//int check_num_in_list(){}

int main()
{
	int i, j, k, l, n, count_code=0, count_symbols=0, dang_count = 0, x, y, z, aa, bb, cc, UDC_flag=0;
	
	char **code_char, **symbols, **dangling_suffix, sample, *temp_char;
	
	printf("\n190420116054 : Manish Prajapati\n\nPractical No. 2: Take set of symbols and associated code. Check whether given code is Prefix or not. Also check whether the code is UDC or not.\n\n");
	printf("Enter the number of symbols you have: ");
	scanf("%d", &n);
	
	code_char = (char **)	malloc(n*sizeof(char *));
	
	symbols = (char **)	malloc(n*sizeof(char *));
	
	printf("\nEnter the symbols and respective code: \n\n");
	
	for(i=0; i<n; i++){
		printf("\nEnter the symbol: ");
		fflush(stdin);
		scanf("%c", &sample);
		count_symbols = 1;
		
		*(symbols+i) = (char*)malloc(count_symbols*sizeof(char));
		
		*(*(symbols + i)+count_symbols-1) = sample;
		
		while(sample!='\n')	{
			scanf("%c", &sample);
			count_symbols++;
			*(symbols+i) = (char*)realloc(*(symbols+i), count_symbols*sizeof(char));
			*(*(symbols + i)+count_symbols-1) = sample;
		}
		
		printf("\nEnter the code of the symbol: ");
		scanf("%c", &sample);
		
		count_code = 1;
		
		*(code_char+i) = (char*)malloc(count_code*sizeof(char));
		
		*(*(code_char + i)+count_code-1) = sample;
		
		while(sample!='\n'){
			scanf("%c", &sample);
			count_code++;
			*(code_char+i) = (char*)realloc(*(code_char+i), count_code*sizeof(char));
			*(*(code_char + i)+count_code-1) = sample;
		}
		
	}
	
	printf("\n\nThe entered data is as follows: \n\n");
	
	for(i=0; i<n; i++){
		printf("%d.  ", i+1);
		
		for(j=0; *(*(symbols+i)+j)!='\n'; j++){
			printf("%c", *(*(symbols+i)+j));
		}
		
		printf("  ");
		
		for(j=0; *(*(code_char+i)+j)!='\n'; j++){
			printf("%c", *(*(code_char+i)+j));
		}
		/*if(*(*(code_char+i)+j)=='\n'){
			printf(" /n");
		}*/
		
		printf("\n");
		
	}
	
	if(check_prefix(code_char, n) == 0){
		
		UDC_flag = 1;
		goto conclusion;
		
	}
	else{					//int i, j, k, l, n, count_code=0, count_symbols=0, dang_count = 0, x, y, z, aa, bb, cc;
	
		dang_count=0;		//	char **code_char, **symbols, **dangling_suffix, sample, *temp_char;
		dang_count++;
		dangling_suffix = (char **)malloc(dang_count*sizeof(char*));
		
		for(i=0; i<n; i++){												//First iteration of spilitting out the code_words and forming the suffixes from code_words only
			for(j=0; j<n; j++){
				if(i==j){
					//continue;)
					//printf("\ni: %d  j: %d", i, j);
				}
				else{
					//printf("\ni: %d  j: %d", i, j);
					l = 0;
					k = 0;
					while(*(*(code_char+i)+l)!='\n' && *(*(code_char+j)+k)!='\n'){
						
						if(*(*(code_char+i)+l) != *(*(code_char+j)+k)){
							break;
						}
						l++;
						k++;
					}
					//printf("\nl: %d   k: %d", l, k);
					
					if(*(*(code_char+i)+l)=='\n' && *(*(code_char+j)+k)=='\n'){
						UDC_flag = 0;
						goto conclusion;
					}
					else{
						if(*(*(code_char+i)+l)=='\n'){
							aa=0;
							temp_char = (char*)malloc((aa+1)*sizeof(char));
							*(temp_char+aa) = *(*(code_char+j)+k);
							k++;
							while(*(*(code_char+j)+k) != '\n'){
								aa++;
								temp_char = (char *)realloc(temp_char, (aa+1)*sizeof(char));
								*(temp_char+aa) = *(*(code_char+j)+k);
								k++;
							}
							aa++;
							temp_char = (char *)realloc(temp_char, (aa+1)*sizeof(char));
							*(temp_char+aa) = *(*(code_char+j)+k);
							
							/*z=0;
							printf("\nTemp_char: ");
							while(*(temp_char+z)!='\n'){
								printf("%c", *(temp_char+z));
								z++;
							} */
							
							if(dang_count==1){
								bb = 0;
								bb++;
								*(dangling_suffix + dang_count-1) = (char *)malloc((aa+1)*sizeof(char));
								while(*(temp_char+bb-1) != '\n'){
									*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);
									bb++;
								}
								*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);
								dang_count++;
							}
							else{								
								if(check_temp_in_dangling_suffix(dangling_suffix, temp_char, dang_count-1)!=0){
									//printf("\n\n For dang_count!=1");
									dangling_suffix = (char **)realloc(dangling_suffix, dang_count*sizeof(char*));
									bb=0;
									bb++;
									*(dangling_suffix + dang_count-1) = (char *)malloc((aa+1)*sizeof(char));
									while(*(temp_char+bb-1) != '\n'){
										*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);
										bb++;
									}
									*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);
									dang_count++;							
								}
								
							}
							
						}
						else if(*(*(code_char+j)+k)=='\n'){
							aa=0;
							temp_char = (char*)malloc((aa+1)*sizeof(char));
							*(temp_char+aa) = *(*(code_char+i)+l);
							l++;
							while(*(*(code_char+i)+l) != '\n'){
								aa++;
								temp_char = (char *)realloc(temp_char, (aa+1)*sizeof(char));
								*(temp_char+aa) = *(*(code_char+i)+l);
								l++;
							}
							aa++;
							temp_char = (char *)realloc(temp_char, (aa+1)*sizeof(char));
							*(temp_char+aa) = *(*(code_char+i)+l);		
							
							/*z=0;
							printf("\nTemp_char: ");
							while(*(temp_char+z)!='\n'){
								printf("%c", *(temp_char+z));
								z++;
							} */
												
							if(dang_count==1){
								bb = 0;
								bb++;
								*(dangling_suffix + dang_count-1) = (char *)malloc((aa+1)*sizeof(char));
								while(*(temp_char+bb-1) != '\n'){
									*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);
									bb++;
								}
								*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);
								dang_count++;
							}
							else{
								//printf("\n\n For dang_count!=1");
								if(check_temp_in_dangling_suffix(dangling_suffix, temp_char, dang_count-1)!=0){
									//printf("\n\n For dang_count!=1");
									dangling_suffix = (char **)realloc(dangling_suffix, dang_count*sizeof(char*));
									bb=0;
									bb++;
									*(dangling_suffix + dang_count-1) = (char *)malloc((aa+1)*sizeof(char));
									while(*(temp_char+bb-1) != '\n'){
										*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);
										bb++;
									}
									*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);		
									dang_count++;					
								}
								
							}
						}
					}
				}
			}
		}
		//printf("\nDang_count: %d", dang_count);
		printf("\n\nThe Dangling suffixes formed are as follows: \n\n");
		for(i=0; i<dang_count-1; i++){										//First iteration of Dangling Suffixes formed printing...
			j=0;
			while(*(*(dangling_suffix+i)+j)!='\n'){
				printf("%c", *(*(dangling_suffix+i)+j));
				j++;
			}
			printf("\n");
		}
		
		for(i=0; i<dang_count-1; i++){
			for(j=0; j<n; j++){						//Checking if any dangling_suffix being a code_word and simulataneously adding new dangling_suffixes
				l = 0;
				k = 0;
				while(*(*(dangling_suffix+i)+l)!='\n' && *(*(code_char+j)+k)!='\n'){
						
					if(*(*(dangling_suffix+i)+l) != *(*(code_char+j)+k)){
						break;
					}
					l++;
					k++;
				}
					
				if(*(*(dangling_suffix+i)+l)=='\n' && *(*(code_char+j)+k)=='\n'){
					//printf("\n\nThe entered codewords are not UNIQUELY DECODABLE.\n");
					UDC_flag=0;
					goto conclusion;
				}
				else if(*(*(dangling_suffix+i)+l)=='\n'){
					aa=0;
					temp_char = (char*)malloc((aa+1)*sizeof(char));
					*(temp_char+aa) = *(*(code_char+j)+k);
					k++;
					while(*(*(code_char+j)+k) != '\n'){
						aa++;
						temp_char = (char *)realloc(temp_char, (aa+1)*sizeof(char));
						*(temp_char+aa) = *(*(code_char+j)+k);
						k++;
					}
					aa++;
					temp_char = (char *)realloc(temp_char, (aa+1)*sizeof(char));
					*(temp_char+aa) = *(*(code_char+j)+k);
					
					if(check_temp_in_dangling_suffix(dangling_suffix, temp_char, dang_count-1)!=0){
						//printf("\n\n For dang_count!=1");			
						dangling_suffix = (char **)realloc(dangling_suffix, dang_count*sizeof(char*));
						bb=0;
						bb++;
						*(dangling_suffix + dang_count-1) = (char *)malloc((aa+1)*sizeof(char));
						while(*(temp_char+bb-1) != '\n'){
							*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);
							bb++;
						}
						*(*(dangling_suffix + dang_count - 1) + bb - 1) = *(temp_char+bb-1);
						dang_count++;							
					}					
				}
			}
		}
		
		printf("\n\nDangling suffixes for next iteration: \n");		//Final Dangling suffixes formed printing...
		for(i=0; i<dang_count-1; i++){
			j=0;
			while(*(*(dangling_suffix+i)+j)!='\n'){
				printf("%c", *(*(dangling_suffix+i)+j));
				j++;
			}
			printf("\n");
		}
		
		if(check_danglings_in_prefix(dangling_suffix, code_char, dang_count-1, n)==1){		//Last checkpoint for concluding given code_words
			UDC_flag = 0;
			goto conclusion;
		}
		else{
			UDC_flag = 1;
			goto conclusion;
		}
		
	}
	
	conclusion:										//Final Conclusion.. Results will print accordingly..
		if(UDC_flag==0){
			printf("\n\nFinal Dangling suffixes formed are: \n");
			for(i=0; i<dang_count-1; i++){
				j=0;
				while(*(*(dangling_suffix+i)+j)!='\n'){
					printf("%c", *(*(dangling_suffix+i)+j));
					j++;
				}
				printf("\n");
			}
			printf("\nThe entered codewords are NOT uniquely decodable code.");
		}
		else{
			printf("\nThe entered codewords are Uniquely Decodable codewords(UDC).");
		}
	
	
	return 0;								//END of Program
}

//OriginalsBy5M4
