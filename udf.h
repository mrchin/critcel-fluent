/*
 * Copyright ANSYS. All Rights Reserved.
 */

#ifndef _FLUENT_UDF_H
#define _FLUENT_UDF_H


/* Header file for User Defined Functions */

#define _UDF 1
#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_DEPRECATE 1

#ifdef UDFCONFIG_H
# include UDFCONFIG_H
#endif

#include "global.h"
#include "mem.h"
#include "para.h"
#include "threads.h"

#include "cudf.h"

#include "amg.h"
#include "case.h"
#include "flow.h"
#include "id.h"
#include "metric.h"
#include "prop.h"
#include "real_gas.h"
#include "lmain.h"

#include "sg_pollut.h"
#include "pollut_nox.h"
#include "pollut_sox.h"
#include "pollut_soot.h"
#include "pollut_hg.h"
#include "sg_mphase.h"
#include "sg_ke.h"
#include "sg_disco.h"
#include "slide.h"
#include "surf.h"
#include "dpm.h"
#include "dpm_types.h"
#include "dpm_tools.h"
#include "dpm_path.h"
#include "dpm_mem.h"
#include "dpm_laws.h"
#include "cl_dpm.h"
#include "isat.h"
#include "rwdata.h"
#include "dynamesh_tools.h"
#include "six_dof.h"
#include "sg_udms.h"
#include "sg_wetsteam.h"
#if RP_NETWORK
#include "sg_network.h"
#endif /* RP_NETWORK */
#include "dual_cell.h"
#if RP_PLBC 
# include "phase_lag.h"
#endif

#if _MSC_VER >= 1400 /* visual studio 2005 */
# ifdef UDF_NT
#  include "ud_io1.h"
# else
#  include "ud_io.h"
# endif
# ifndef USE_FLUENT_IO_API
# define USE_FLUENT_IO_API 1
# endif
#else
# ifndef USE_FLUENT_IO_API
# define USE_FLUENT_IO_API 0
# endif
#endif /* _MSC_VER >= 1400 */

#include "machine.h"
#include "sg_reacting_channel.h"


#define DEFINE_DIFFUSIVITY(name, c, t, i) real name(cell_t c, Thread *t, int i)
#define DEFINE_PROFILE(name, t, i) void name(Thread *t, int i)
#define DEFINE_PROPERTY(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_SPECIFIC_HEAT(name, T, Tref, h, yi) real name(real T, real Tref, real *h, real *yi)
#define DEFINE_DPM_PROPERTY(name, c, t, p, T) \
  real name(cell_t c, Thread *t, Tracked_Particle *p, real T)
#define DEFINE_EXCHANGE_PROPERTY(name, c, mixture_thread, second_column_phase_index, first_column_phase_index) \
real name(cell_t c, Thread *mixture_thread, int second_column_phase_index, int first_column_phase_index)
#define DEFINE_BOILING_PROPERTY(name, f,t, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index) \
real name(face_t f,Thread *t,cell_t c,Thread *mixture_thread, int from_phase_index, int from_species_index, int to_phase_index, int to_species_index)
#define DEFINE_VECTOR_EXCHANGE_PROPERTY(name, c, mixture_thread, second_column_phase_index, first_column_phase_index, vector_result) \
void name(cell_t c, Thread *mixture_thread, int second_column_phase_index, int first_column_phase_index, real *vector_result)
#define DEFINE_MASS_TRANSFER(name, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index) \
real name(cell_t c, Thread *mixture_thread, int from_phase_index, int from_species_index, int to_phase_index, int to_species_index)
#define DEFINE_LINEARIZED_MASS_TRANSFER(name, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index, lin_from, lin_to) \
real name(cell_t c, Thread *mixture_thread, int from_phase_index, int from_species_index, int to_phase_index, int to_species_index, real *lin_from, real *lin_to)
#define DEFINE_HET_RXN_RATE(name, c, t, hr, mw, yi, rr, rr_t) \
  void name(cell_t c, Thread *t, Hetero_Reaction *hr, real **mw, real **yi, real *rr, real *rr_t)
#define DEFINE_SOURCE(name, c, t, dS, i) \
  real name(cell_t c, Thread *t, real dS[], int i)
#define DEFINE_INIT(name, domain) void name(Domain *domain)
#define DEFINE_ADJUST(name, domain) void name(Domain *domain)
#define DEFINE_UDS_FLUX(name, f, t, i) real name(face_t f, Thread *t, int i)
#define DEFINE_UDS_UNSTEADY(name, c, t, i, apu, su) \
  void name(cell_t c, Thread *t, int i, real *apu, real *su)
#define DEFINE_HEAT_FLUX(name, f, t, c0, t0, cid, cir) \
  void name(face_t f, Thread *t, cell_t c0, Thread *t0, real cid[], real cir[])
#define DEFINE_VR_RATE(name, c, t, r, mw, yi, rr, rr_t) \
  void name(cell_t c, Thread *t, \
	    Reaction *r, real *mw, real *yi, real *rr, real *rr_t)
#define DEFINE_NET_REACTION_RATE(name, c, t, particle, pressure, temp, yi, rr, jac) \
  void name(cell_t c, Thread* t, Particle *particle, double *pressure, double *temp, double *yi, double *rr, double *jac)
#define DEFINE_SR_RATE(name, f, t, r, mw, yi, rr) \
  void name(face_t f, Thread *t, \
	    Reaction *r, double *mw, double *yi, double *rr)
#define DEFINE_PR_RATE(name, c, t, r, mw, ci, p, sf, dif_index, cat_index, rr) \
  void name(cell_t c, Thread *t, \
	    Reaction *r, real *mw, real *ci, Tracked_Particle *p, \
        real *sf , int dif_index, int cat_index, real *rr)
#define DEFINE_EC_RATE(name, f, t, r, eta, i, dideta) \
  void name(face_t f, Thread *t, Reaction *r, real eta, real *i, real *dideta)
#define DEFINE_TURB_PREMIX_SOURCE(name, c, t, turbulent_flame_speed, source) \
  void name(cell_t c, Thread *t, real *turbulent_flame_speed, real *source)
#define DEFINE_ECFM_SOURCE(name, c, t, source, ap) \
  void name(cell_t c, Thread *t, real *source, real *ap)
#define DEFINE_ECFM_SPARK_SOURCE(name, c, t, source, ap) \
  void name(cell_t c, Thread *t, real *source, real *ap)
#define DEFINE_GEQN_SOURCE(name, c, t, source, ap) \
  void name(cell_t c, Thread *t, real *source, real *ap)
#define DEFINE_SPARK_GEOM(name, c, t) int name(cell_t c, Thread *t)
#define DEFINE_IGNITE_SOURCE(name, c, t, source) \
  void name(cell_t c, Thread *t, real *source)
#define DEFINE_THICKENED_FLAME_MODEL(name, c, t, f, e, omega) \
  void name(cell_t c, Thread *t, real *f, real *e, real *omega)
#define DEFINE_DPM_BODY_FORCE(name, p, i) real name(Tracked_Particle *p, int i)
#define DEFINE_DPM_DRAG(name, Re, p) real name(real Re, Tracked_Particle *p)
#define DEFINE_DPM_SOURCE(name, c, t, S, strength, p) \
  void name(cell_t c, Thread *t, dpms_t *S, real strength, Tracked_Particle *p)
#define DEFINE_DPM_OUTPUT(name, header, fp, p, t, plane) \
  void name(int header, FILE *fp, Tracked_Particle *p, Thread *t, Plane *plane)
#define DEFINE_DPM_EROSION(name, p, t, f, normal, alpha, Vmag, mdot) \
  void name(Tracked_Particle *p, Thread *t, face_t f, real normal[], \
	    real alpha, real Vmag, real mdot)
#define DEFINE_DPM_SCALAR_UPDATE(name, c, t, initialize, p) \
  void name(cell_t c, Thread *t, int initialize, Tracked_Particle *p)
#define DEFINE_DPM_SPRAY_COLLIDE(name, tp, p) \
  void name(Tracked_Particle *tp, Particle *p)
#define DEFINE_DPM_LAW(name, p, ci) void name(Tracked_Particle *p, int ci)
#define DEFINE_DPM_SWITCH(name, p, ci) void name(Tracked_Particle *p, int ci)
#define DEFINE_DPM_INJECTION_INIT(name, I) void name(Injection *I)
#define DEFINE_DPM_BC(name, p, t, f, normal, dim) \
  int name(Tracked_Particle *p, Thread *t, face_t f, real normal[], int dim)
#define DEFINE_DPM_TIMESTEP(name, p, ts) real name(Tracked_Particle *p,real ts)
#define DEFINE_DPM_VP_EQUILIB(name, p, Tp, cvap_surf, Z) \
  void name(Tracked_Particle *p, real Tp, real *cvap_surf, real *Z)
#define DEFINE_DPM_HEAT_MASS(name, p, Cp, hgas, hvap, cvap_surf, Z, dydt, dzdt) \
  void name(Tracked_Particle *p, real Cp, \
            real *hgas, real *hvap, real *cvap_surf, real Z, real *dydt, dpms_t *dzdt)
#define DEFINE_SCAT_PHASE_FUNC(name, c, f) \
     real name(real c, real *f)
#define DEFINE_CAVITATION_RATE(name, c, t, p, rhoV, rhoL, vofV, p_v, cigma, f_gas, m_dot) \
  void name(cell_t c, Thread *t, real *p, real *rhoV, real *rhoL, real *vofV, \
	                 real *p_v, real *cigma, real *f_gas, real *m_dot)
#define DEFINE_RW_FILE(name, fp) void name(FILE *fp)
#define DEFINE_ON_DEMAND(name) void name(void)
#define DEFINE_OUTPUT_PARAMETER(name, n, parlist) real name (int n, real* parlist)
#define DEFINE_EXECUTE_AT_END(name) void name(void)
#define DEFINE_TURBULENT_VISCOSITY(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_K(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_D(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_O(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_T(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_T_WALL(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_TURB_SCHMIDT(name, c, t, i) real name(cell_t c, Thread *t, int i)
#define DEFINE_WALL_FUNCTIONS(name, f, t, c0, t0, wf_ret, yPlus, Emod) \
  real name(face_t f, Thread *t, cell_t c0, Thread *t0, int wf_ret, real yPlus, real Emod)
#define DEFINE_TRANS_FLENGTH(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_TRANS_RETHETA_C(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_TRANS_RETHETA_T(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_TRANS_GEOMRGH(name, c, t) real name(cell_t c, Thread *t)
#define DEFINE_NOX_RATE(name, c, t, Pollut, Pollut_Par, NOx) \
  void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, NOx_Parameter *NOx)
#define DEFINE_SOOT_PRECURSOR(name, Pollut, Pollut_Par, Soot) \
  real name(Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot)
#define DEFINE_SOOT_OXIDATION_RATE(name, c, t, Pollut, Pollut_Par, Soot, soot_oxi_rates) \
  void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot, real *soot_oxi_rates)
#define DEFINE_SOX_RATE(name, c, t, Pollut, Pollut_Par, SOx) \
  void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, SOx_Parameter *SOx)
#define DEFINE_HG_RATE(name, c, t, Pollut, Pollut_Par, Hg) \
  void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Hg_Parameter *Hg)
#define DEFINE_CHEM_STEP(name, c, t, p, num_p, n_spe, dt, pres, temp, yk)	\
  void name(cell_t c, Thread *t, Particle *p, int num_p, int n_spe, double *dt, double *pres, double *temp, double *yk)
#define DEFINE_CPHI(name, c, t) \
  real name(cell_t c, Thread *t)
#define DEFINE_PDF_TRANSPORT_DENSITY(name, c, t, p) \
  real name(cell_t c, Thread *t, Particle *p)
#define DEFINE_GRID_MOTION(name, d, dt, time, dtime) \
  void name(Domain *d, Dynamic_Thread *dt, real time, real dtime)
#define DEFINE_CG_MOTION(name, dt, vel, omega, time, dtime)		\
  void name(Dynamic_Thread *dt, real vel[], real omega[], real time, real dtime)
#define DEFINE_GEOM(name, d, dt, position) \
  void name(Domain *d, Dynamic_Thread *dt, real *position)
#define DEFINE_CONTACT(name, dt, contacts) \
  void name(Dynamic_Thread *dt, Objp *contacts)
#define DEFINE_SDOF_PROPERTIES(name, properties, dt, time, dtime) \
  void name(real *properties, Dynamic_Thread *dt, real time, real dtime)
#define DEFINE_DELTAT(name, domain) real name(Domain *domain)

#define DEFINE_DOM_SOURCE(name,c,t,ni,nb,emission,in_scattering,abs_coeff,scat_coeff)\
  void name(cell_t c, Thread* t, int ni, int nb, real *emission, real *in_scattering,\
             real *abs_coeff, real *scat_coeff)
#define DEFINE_DOM_BC_ADJUST(name, domain) void name(Domain *domain)
#define DEFINE_DOM_DIFFUSE_REFLECTIVITY(name,t,nb,n_a,n_b,diff_ref_a, \
diff_tran_a, diff_ref_b, diff_tran_b) \
void name(Thread *t, int nb,  real n_a, real n_b, real *diff_ref_a, \
real *diff_tran_a, real *diff_ref_b, real *diff_tran_b)

#define DEFINE_DOM_SPECULAR_REFLECTIVITY(name,f,t,nb,n_a, n_b, \
ray_direction,  e_n, total_internal_reflection, \
specular_reflectivity, specular_transmissivity) \
 void name(face_t f, Thread *t, int nb,  real n_a, real n_b , \
real ray_direction[], real e_n[],  int *total_internal_reflection, \
real *specular_reflectivity,  real *specular_transmissivity)

#define DEFINE_EMISSIVITY_WEIGHTING_FACTOR(name,c,t,T,nb,emissivity_weighting_factor)\
  void name(cell_t c, Thread* t, real T, int nb, real *emissivity_weighting_factor)

#define DEFINE_SOLAR_TRANSMISSIVITY(name, f, t, e_n, e_sun, trans_V, trans_I, \
absorptivity_V, absorptivity_I) \
void name(face_t f, Thread *t, double e_n[], double e_sun[], \
double *trans_V, double *trans_I, double *absorptivity_V, double *absorptivity_I)


#define DEFINE_SOLAR_INTENSITY(name, sun_x, sun_y, sun_z, S_hour, S_minute) \
   real name(real sun_x, real sun_y, real sun_z, int S_hour,int S_minute) 
#define DEFINE_GRAY_BAND_ABS_COEFF(name, c, t, nb)  \
   real name(cell_t c, Thread *t, int nb) 

#define DEFINE_WSGGM_ABS_COEFF(name, c, t, xi, p_t, s, soot_conc, Tcell, nb, ab_wsggm, ab_soot)  \
   void name(cell_t c, Thread *t, real xi[], real p_t, real s, real soot_conc, real Tcell, int nb, real *ab_wsggm, real *ab_soot) 

#define DEFINE_ANISOTROPIC_DIFFUSIVITY(name, c, t, ns, dmatrix)		\
  void name(cell_t c, Thread *t, int ns, real dmatrix[ND_ND][ND_ND])

#define DEFINE_ANISOTROPIC_CONDUCTIVITY(name, c, t, dmatrix)		\
  void name(cell_t c, Thread *t, real dmatrix[ND_ND][ND_ND])


#define DEFINE_DYNAMIC_ZONE_PROPERTY(name, dt, lh)	\
  void name(Dynamic_Thread *dt, real *lh)

#define DEFINE_NETWORK_NODE_PROP(name, network_id, network_cell_id)	\
  real name(int network_id, int network_cell_id)

#define DEFINE_NETWORK_LINK_PROP(name, network_id, network_cell_id, network_cellnb, nbflag) \
  real name(int network_id, int network_cell_id, int network_cellnb, int nbflag)
#define DEFINE_NETWORK_END_PROP(name, networkend_id)	\
  real name(int networkend_id)

#define DEFINE_EVAL(name, domain)		\
  cxboolean name(Domain *domain)

#define DEFINE_EXECUTE_ON_LOADING(name, libname) void name(char *libname)
#define DEFINE_EXECUTE_FROM_GUI(name, libname, mode) void name(char *libname, int mode)
#define DEFINE_EXECUTE_AFTER_CASE(name, libname) void name(char *libname)
#define DEFINE_EXECUTE_AFTER_DATA(name, libname) void name(char *libname)

#define DEFINE_MATRIX_SOLVER(name, controls, fine, r0) \
    int name(AMG_Controls controls, Level fine, real r0[])

#define DEFINE_EXECUTE_AT_EXIT(name) void name(void)
/*population balance udf's*/

#define DEFINE_PB_BREAK_UP_RATE_FREQ(name, cell, thread, d_1) \
   real name(cell_t cell, Thread *thread, real d_1)
#define DEFINE_PB_BREAK_UP_RATE_PDF(name, cell, thread_1, d_1, thread_2, d_2) \
  real name(cell_t cell, Thread *thread_1, real d_1, Thread *thread_2, real d_2)
#define DEFINE_PB_COALESCENCE_RATE(name, cell, thread_1, d_1, thread_2, d_2) \
  real name(cell_t cell, Thread *thread_1, real d_1, Thread *thread_2, real d_2)
#define DEFINE_PB_NUCLEATION_RATE(name, cell, thread)\
   real name(cell_t cell, Thread *thread)
#define DEFINE_PB_GROWTH_RATE(name, cell, thread, d_i)\
   real name(cell_t cell, Thread *thread, real d_i)

#define DEFINE_SOLIDIFICATION_PARAMS(name,c,t,Amush,back_diff_beta) \
        void name(cell_t c, Thread *t, real *Amush, real *back_diff_beta)

#define DEFINE_TRANSIENT_PROFILE(name, current_time) real name(real current_time)

#define DEFINE_ZONE_MOTION(name,omega,axis,origin,velocity,time,dtime) \
        void name(real *omega, real axis[ND_3], real origin[ND_3], real velocity[ND_3],real time,real dtime)

/* backward compatibility */
#define C_PART(c,t) C_PART_ACTIVE(c,t)

#define DEFINE_PDF_TABLE(name, m, c, t, fmean, fvar, fmean2, fvar2, h, what, prop, x, s_pollut) \
        void name(Material * m, cell_t c, Thread *t, real fmean, real fvar, real fmean2, real fvar2, real h, int what, \
         real prop[], real * x, Pollut_Rate * s_pollut[])

#define DEFINE_REACTING_CHANNEL_SOLVER(name,params,inlet_state,dist,dt,wall_temp,wall_hf,compute_htc)\
        void name(int *params,real *inlet_state, real *dist, real *dt, real *wall_temp, real *wall_hf, cxboolean *compute_htc)
       
#define DEFINE_REACTING_CHANNEL_BC(name,i,group) void name(int i, Channel_Group *group)
/* end of udf.h */

#endif /* _FLUENT_UDF_H */
