#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*! ------------------------------------------------------------

  \struct absorp

  \brief measures

  ------------------------------------------------------------*/

typedef struct{
		float acr;  /*!< AC R */
		float dcr;  /*!< DC R */
		float acir;  /*!< AC IR */
		float dcir;  /*!< DC IR */
	} absorp;

/*! ------------------------------------------------------------

  \struct oxy

  \brief

  ------------------------------------------------------------*/

typedef struct{
		int spo2;  /*!< SPO2 */
		int pouls;  /*!< Pouls */
	} oxy;

/*! ------------------------------------------------------------

	\struct param_fir

	\brief

	------------------------------------------------------------*/

typedef struct{
		float coef[51]; //les 51 coeffients
		absorp precedentes[51]; //les 51 dernieres valeurs
		int derniere; //indice dernière valeur
		int premire; //indice première valeur
	} param_fir;

	/*! ------------------------------------------------------------

		\struct param_iir

		\brief

		------------------------------------------------------------*/
typedef struct{

		float alpha;
		absorp precedenteValeurSignale; //les 51 dernieres valeurs
		absorp precedenteValeurFiltree; //y(n-1)

	} param_iir;



#endif // DEFINE_H