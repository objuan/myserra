

import logging

logger = logging.getLogger(__name__)

# LAB VARS
LAB_EC_VALUE = 13
LAB_EC_K = 14
LAB_TEMPERATURE = 15
LAB_PH_VALUE = 16
LAB_PH_VOLT = 17
LAB_PH_REF_4 = 18
LAB_PH_REF_6 = 19
LAB_DISTANCE = 20
LAB_DISTANCE_EMPTY = 21
LAB_BASE_AREA = 29*31

# LAB PUMPS
LAB_TANK1_IN =  9
LAB_TANK1_OUT =  10

LAB_MIX_PUNP =  14

LAB_EC_IN_A =  11
LAB_EC_IN_B =  12
LAB_PH_IN =  13
LAB_WATER_IN =  15
#### PARAMETRI DA SETTARE CON PROVE ###############

LAB_MIXER_TIME_SECS = 1

# tempo necessario per avere tot millilitri in secondi
#LAB_PUMP_6MM_ML_PER_SECONDS = 1

# PH_DOWN, quantità necessaria per litro per buttare giù di 0.1 il PH
LAB_PH_DOWN_1_ML_PER_LITRES =1

# EC_DOWN, quantità necessaria per litro per buttare giù di 1000 l'ec 
LAB_WATER_EC_1000_X_LITRO_IN_LITRES =1


#EC
# da aggiungere ad un litro in millilitri  per avere 1000 EC
#ATAMI
# Da 1 a 3 ml per A e da 1 a 3 ml per  B per litro d’acqua
LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML =1
LAB_ATAMI_EC_B_1000_X_LITRO_IN_ML =1


