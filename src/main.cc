#include <global.h>
#include <checkArgs.hpp>


uint64_t* OMP_SERIAL = nullptr;
uint64_t* OMP_PARALELO = nullptr;
uint64_t OMP_SUMA_P = 0;
uint64_t OMP_SUMA_S = 0;


void llenado_OMP(size_t tipo, size_t hilos, size_t tamArr,size_t inf, size_t sup){

			std::random_device device;
			std::mt19937 rng(device());
			std::uniform_int_distribution<uint32_t> nRandom(inf, sup);
			uint32_t number = nRandom(rng);	

			
			switch (tipo)
			{
			case 0:		
						#pragma omp parallel for  num_threads(hilos)
						for(size_t i = 0; i < tamArr; ++i){	
							OMP_PARALELO[i] =number;
							
						}
				break;
			case 1:		
						#pragma omp parallel for  num_threads(1)
						for(size_t i = 0; i < tamArr; ++i){	
							OMP_SERIAL[i] = number;
							
						}
				break;
			
			}

					


}

void suma_OMP(size_t tipo, size_t hilos, size_t tamArr){
	

			
			switch(tipo){
				case 0: 
						#pragma omp parallel for reduction(+:OMP_SUMA_P) num_threads(hilos)
						for(size_t i = 0; i < tamArr; ++i){
							OMP_SUMA_P += OMP_PARALELO[i];
						}
					
					break;
				case 1:
						#pragma omp parallel for reduction(+:OMP_SUMA_S) num_threads(hilos)
						for(size_t i = 0; i < tamArr; ++i){
							OMP_SUMA_S += OMP_PARALELO[i];
						}
					
					
					break;
			}
}


int main(int argc, char** argv){
	
	uint64_t tamanoArreglo;
	uint64_t numThreads;
	uint64_t limiteSuperior;
	uint64_t limiteInferior;
	
	auto argumentos = (std::shared_ptr<checkArgs>) new checkArgs(argc, argv);
	tamanoArreglo = argumentos->getArgs().tamArreglo;
	numThreads     = argumentos->getArgs().numThreads;
	limiteSuperior = argumentos->getArgs().limSuperior;
	limiteInferior = argumentos->getArgs().limInferior;

	OMP_SERIAL = new uint64_t[tamanoArreglo];
	OMP_PARALELO = new uint64_t[tamanoArreglo];;

//--------------llenado OMP PARALELO---------------//

	auto start = std::chrono::high_resolution_clock::now();

	llenado_OMP(0,numThreads,tamanoArreglo,limiteInferior,limiteSuperior);

	auto end     = std::chrono::high_resolution_clock::now(); 
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeLLENADO_OMP_P = elapsed.count();

//--------------llenado OMP SERIAL---------------//

	start = std::chrono::high_resolution_clock::now();

	llenado_OMP(1,1,tamanoArreglo,limiteInferior,limiteSuperior);

	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeLLENADO_OMP_S = elapsed.count();

//--------------SUMA OMP PARALELO---------------//

	start = std::chrono::high_resolution_clock::now();

	suma_OMP(0,numThreads,tamanoArreglo);

	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeSUMA_OMP_P = elapsed.count();

//--------------SUMA OMP SERIAL---------------//

	start = std::chrono::high_resolution_clock::now();

	suma_OMP(1,1,tamanoArreglo);

	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeSUMA_OMP_S = elapsed.count();

//----------------resultados------------------//
	std::cout << "-----------datos ingresados----------" << std::endl;	
	std::cout << "tamaño arreglo: " << tamanoArreglo << std::endl;
	std::cout << "Threads  : " << numThreads     << std::endl;
	std::cout << "limite inferior: " << limiteInferior << std::endl;
	std::cout << "limte superior  : " << limiteSuperior << std::endl;
	std::cout << "-----------resultados de sumas OMP----------" << std::endl;	
	std::cout << "suma OMP paralelo :"  << OMP_SUMA_P  << std::endl;
	std::cout << "suma OMP serial :"  << OMP_SUMA_S << std::endl;

	std::cout << "--------------Tiempos OMP-------------- :"  << std::endl;

	std::cout << "Tiempo llenado OMP paralelo :"  << totalTimeLLENADO_OMP_P << "[ms]" << std::endl;
	std::cout << "Tiempo llenado OMP serial :"  << totalTimeLLENADO_OMP_S << "[ms]" << std::endl;
	std::cout << "Tiempo suma OMP paralela :"  << totalTimeSUMA_OMP_P << "[ms]" << std::endl;
	std::cout << "Tiempo suma OMP serial :"  << totalTimeSUMA_OMP_S << "[ms]" << std::endl;

	
	
	return(EXIT_SUCCESS);
}
