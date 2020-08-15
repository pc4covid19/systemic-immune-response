# systemic-immune-response

Integrate immune response (ODE) with PhysiCell

For now, just compile with `make` and run `COVID19` to see the dummy `lymphatic_main_model` being invoked. Files of interest are `custom_modules/lymphatic_submodel.{h,cpp}` and `main.cpp`.

## Changes from original 3.2 code
* added `custom_modules/lymphatic_submodel.{h,cpp}`

Not yet using, but also:
* added `beta/setup_libroadrunner.py`
* added `intracellular/PhysiCell_intracellular.h`
* added `std::string sbml_filename;` into `class Cell_Definition` (in `core/PhysiCell_cell.h`)
* incorporate intracellular (SBML, libRoadrunner) info into `custom.{h,cpp}`
  * see `assign_SBML_model( Cell* pC )` in `custom.cpp`
  * see extra code in `create_cell_types( void )` where we obtain the desired SBML species' indices.
* added `Make-sbml`

# Immune response ODE model
Tarun provided a Tellurium version (`tellurium_ODE_model`) of the immune response ODE model. We converted it to an Antimony file (`ode_model.ant`), loaded it into Tellurium, and generated a SBML model (`immune_response.xml`).
```
In [1]: import tellurium as te

In [2]: r = te.loadAntimonyModel('ode_model.ant')
Warning: species 'D' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'Ev' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'Tc' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'Da' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'Dm' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'B' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'Pss' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'Psn' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'Pls' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'Pln' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'sIgM' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'nIgM' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'sIgG' has neither initial amount nor concentration set.  Setting initial concentration to 0.0
Warning: species 'nIgG' has neither initial amount nor concentration set.  Setting initial concentration to 0.0


In [3]: print(r.getCurrentSBML())
# --> outputs SBML which we copy/paste into immune_response.xml
```

## COPASI
Using COPASI, one can `File -> Import SBML` the model and examine it in various ways.

![Species "B"](/images/copasi_species_B.png)
