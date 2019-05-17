#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <check.h>

#include "afficher.h"
#include "selection.h"
#include "symetrie_horizontale.h"
#include "symetrie_verticale.h"

START_TEST(test_afficher)
{
	SDL_Surface *s;
	s = SDL_LoadBMP("lac_en_montagne.bmp");
	ck_assert_int_eq(afficher(s),1);
}
END_TEST

START_TEST(test_selection)
{
	char *nom = "lac_en_montagne.bmp";
	ck_assert_int_eq(selectionner_image(nom,100,100,100,100),1);
}
END_TEST

START_TEST(test_symHor)
{
	SDL_Surface *s;
	s = SDL_LoadBMP("lac_en_montagne.bmp");
	ck_assert_int_eq(symetrie_horizontale_image(s),1);
}
END_TEST

START_TEST(test_symVer)
{
	SDL_Surface *s;
	s = SDL_LoadBMP("lac_en_montagne.bmp");
	ck_assert_int_eq(symetrie_verticale_image(s),1);
}
END_TEST



Suite *test_suite(void){
	Suite *s;
	TCase *tc_core; 
	TCase *tc_limits;
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core,test_afficher);
	tc_limits = tcase_create("Limits");
	tcase_add_test(tc_limits,test_selection);
	tcase_add_test(tc_limits,test_symHor);
	tcase_add_test(tc_limits,test_symVer);
	s = suite_create("LesTests");	
	suite_add_tcase(s,tc_core);
	suite_add_tcase(s,tc_limits);
	

	return s;
}


int main(int argc, char* argv[]){
	Suite *s;
	SRunner *sr;
	int number_failed;

	s = test_suite();
	sr = srunner_create(s);
	
	srunner_run_all(sr,CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? 0:1;
}

