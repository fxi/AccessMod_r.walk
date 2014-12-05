#include <stdio.h>
#include <math.h>
#include <gsl/gsl_poly.h>
/* Accesmod custom functions*/

/*------------------------------------------------------------------
 *               bicycle function                   
 *                                                   
 * see http://www.kreuzotter.de/english/espeed.htm  
 * constant to  put in an external file after developementi
 *-----------------------------------------------------------------*/

/* Define constant and variables */
const float W=0; /* wind speed */
const float Hnn=350; /* Elevation above sea */
const float Tc=20;  /* external temperature influence air density */
const float mbike=12; /* mass of bike */
const float mrider=80; /* mass of rider */
const float CdA=0.4; /*Effective Drag Area */
const float Cr=0.008; /* Rolling resistance coefficient (between 0.0025 and 0.008) */
const float CrV=0.2; /* approximated to 0.1 */
const float Cm=1.09; /* between 1.03 and 1.09 */
const float rho0=1.225; /* air density at sea level, 0°C, kg/m3 */
const float p0=101325; /* air pressur at sea level, 0°C,Pa */
const float g=9.81; /* m/s2 */
const float e=2.71828;



/* flat values (used in formula to get initial power for given velocity).*/
const  float betaFlat=0;
const  float CrVnFlat=CrV;
const  float CrVFlat=CrV;



/* Actual function to get final velocity. Velocity (expected velocity on flat) and slope*/
double velocBicycle(float veloc, float slope)
{ 
  double a,b,c,x0,x1,x2 ;/* var in cubic eq..*/
  int roots; /*ouput roots*/
  double velocFinal; /*final velocity after slope and phys. vars. */
  float power,P ;/* Power in W */
  float Frg; /*rol friction*/
  /* rolling friction on a flat surface */
  float FrgFlat=g*(mbike+mrider)*(Cr*cos(betaFlat)+sin(betaFlat));
  veloc = veloc/3.6; /* value in meter and second*/
  /* Temperature in deg. kelvin ! */
  float T=Tc+273.15; 

  /* air density via barometric formula  */
  float rho=rho0*(373/T)*pow(e,(-rho0*g*(Hnn/p0)));
  /* power needed for a given base speed*/
  P = Cm*veloc*(CdA*(rho/2)*pow(veloc+W,2)+FrgFlat+veloc+CrVnFlat);
  /*slope in radian*/  
  float beta=atan(slope); 
  /**/
  float CrVn=CrV*cos(beta);
  /* rolling friction */
  Frg=g*(mbike+mrider)*(Cr*cos(beta)+sin(beta));
  /* spped cubic function */
  a=(W+(CrVn/(CdA*rho)));
  b=pow(W,2)+((2*Frg)/(CdA*rho));
  c=-((2*P)/(Cm*CdA*rho));
  /* solve equation with gsl */
  roots = gsl_poly_solve_cubic(a,b,c,&x0,&x1,&x2);
  /* get the absolute speed in km/h. Why does the function return a negative value for negative slope ??  */
  /*velocFinal=x0*3.6;*/
  velocFinal=fabs(x0*3.6);
  return velocFinal;
}

/*------------------------------------------------------------------
 *               hiking function
 *
 * Tobler hiking function:
 * tobler is based on a speed of 6 km/h. 
 * here, we want to set another base velocity: veloc.
 * So we extract coefficient to allow a modified version of tobler's formula.
 * see http://www.kreuzotter.de/english/espeed.htm  
 * constant to  put in an external file after developementi 
 *-----------------------------------------------------------------*/
double velocWalk(double veloc, double slope)
{
  /* use fabs instead of abs...*/
  double topVelocity,velocFinal,testVal;
  topVelocity = veloc/exp(-0.175); /* -0.175 = -3.5*0.05 */
  velocFinal = exp(-3.5*fabs(slope+0.05))*topVelocity;
  return velocFinal;
};

/*-------------------------------------------------------------------             
 *              Motorized vehicle  function 
 *
 * doesnt take in account slope. Expected to applied on road cells !
 * but.. in case of very montaneous roads, with a heavy truck:
 * The bicycle function could apply with other constants of total weight, drag area, resistance,...
 *   
 *-----------------------------------------------------------------*/
double velocMotor(double veloc, double slope)
{
  double velocFinal = veloc;
  return velocFinal;
};




/*-------------------------------------------------------------------             
 *              modSwitcher
 *  switch through mod of one cell to determine
 * the appropriate function to use for final velocity.
 *
 *-----------------------------------------------------------------*/
double modSwitcher(int mod, double veloc, double slope)
{
  double v;
  switch(mod)
  {
    case 1:
      v=velocWalk(veloc,slope);
      break;
    case 2:
      v=velocBicycle(veloc,slope);
      break;
    case 3:
      v=velocMotor(veloc,slope);
      break;
    default: 
      v=0;
  };
  return v;
};

/*-------------------------------------------------------------------             
 *              costManager
 *          -- main function --
 * Check for the group of cells (2 if knightmove is false, 4 otherwise) to
 * extract the mode of transportation and velocity from the velocity map 
 * ------------- Value of mode 
 * veloc map is encoded by step of thousend
 * 1 = walking 
 * 2 = bicycle
 * 3 = motorized 
 * ------------- Additional informations
 * modVelocAdj1-3 = extracted from velocity map. E.g. 2004 -> 2 is for bicycle, 4 the speed in kmh
 * slope = slope in % (r.walk :: check_dtm)
 * dist = distance between cells (r.walk :: E,W,S,N_fac or Diag_fac or V_DIAG_fac ) 
 * total_reviewed = if knight's move, 16, else 8. (r.walk total_reviewed)
 *-----------------------------------------------------------------*/
double costManager(int modVeloc,int modVelocAdj1,int modVelocAdj2,int modVelocAdj3, double slope, double dist, int total_reviewed)
{
  /* current cell values */
  int mod       = floor(modVeloc/1000);
  int veloc     = round(modVeloc-mod*1000);
  /* adjacent cell mod of transportations*/
  int modAdj1   = floor(modVelocAdj1/1000);
  int modAdj2   = floor(modVelocAdj2/1000);
  int modAdj3   = floor(modVelocAdj3/1000);
  /* adjacent cell velocity in km/h */
  int velocAdj1 = round(modVelocAdj1-modAdj1*1000);
  int velocAdj2 = round(modVelocAdj2-modAdj2*1000);
  int velocAdj3 = round(modVelocAdj3-modAdj3*1000);
 
  /* output var */
  double velocCurrent;
  double velocFinal;
  double costTimeFinal;
  /* get velocity for the present cell according to its mode,velocity and slope*/
  velocCurrent = modSwitcher(mod,veloc,slope);
  /*case of knight's move (3 adjacent cells) there is 4 cell to compute.
   * TODO check for equality between cells mode AND velocity to avoid recalculation 
   * at every step. Caution : in the worst case, all 4 cells have different velocity
   * AND mode of transportation. A lot of possibilities. */
  if(total_reviewed==16){
    velocFinal=(
        velocCurrent+
        modSwitcher(modAdj1,velocAdj1,slope)+
        modSwitcher(modAdj2,velocAdj2,slope)+
        modSwitcher(modAdj3,velocAdj3,slope)
        )/4; 
  }else{
    velocFinal=(velocCurrent+modSwitcher(modAdj1,velocAdj1,slope))/2; 
  };

  /* Return cost (s) for the provided distance*/
  costTimeFinal=(1/(velocFinal/3.6))*dist;
  return costTimeFinal;
}

