#include "./external_immune.h" 

using namespace PhysiCell; 

std::string external_immune_version = "0.0.1"; 

Submodel_Information external_immune_info; 


void external_immune_model_setup( void )
{
		// set version
	external_immune_info.name = "external immune"; 
	external_immune_info.version = external_immune_version; 
		// set functions 
	external_immune_info.main_function = external_immune_model; 
	external_immune_info.phenotype_function = NULL; 
	external_immune_info.mechanics_function = NULL; 
		// what microenvironment variables do I need? 

		// what custom data do I need? 
	//external_immune_info.parameters.doubles.push_back( "DM" );
	//external_immune_info.parameters.doubles.push_back( "TC" );

	// submodel_registry.register_model( internal_viral_dynamics_info ); 
	external_immune_info.register_model();
	
	return; 
}

void external_immune_model( double dt )
{
	// bookkeeping -- find microenvironment variables we need

	extern double DM;
	extern double TC;
	static double dC = parameters.doubles( "TC_death_rate" ); 
	static double pT1 = parameters.doubles( "max_activation_TC" ) * 1000; 
	static double pT2 = parameters.doubles( "half_max_activation_TC" )/10; 
	static double dT1 = parameters.doubles( "max_clearance_TC" ); 
	static double dT2 = parameters.doubles( "half_max_clearance_TC" )/10; 
	static double Tc0 = parameters.doubles( "TC_population_threshold" ) * 100; 
	static double immunevolume = 1;
	static double dDm = 0.5 / 1440;
	static double addme = 0;
		
	// actual model goes here 
	
	// TC update
	double dR_TC = dt * dC * Tc0 / immunevolume ;

	// DM Tc recruitment
	double dR_TCD = dt * pT1 * DM * TC / immunevolume / ( DM + pT2) ;
	
	// DM Tc decay
	double dR_TC16 = dt * dT1 * DM * TC / immunevolume / ( DM + dT2) ;
	
	// TC decay
	double dR_TC14 = dt * dC * TC / immunevolume ;
	
	addme += dR_TC + dR_TCD - dR_TC16 - dR_TC14;
	
	// std::cout<< addme << std::endl; //for debug
	
	if( addme < TC )
	{ addme = -TC; }
	
	TC += addme;
	
	// DM decay
	double dR_DM = dt * dDm * DM / immunevolume;
	if( dR_DM > DM )
	{ dR_DM = DM; }
	DM -= dR_DM; // decay DM
	
	return; 
}
	
