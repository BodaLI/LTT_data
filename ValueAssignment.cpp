void AllData::PDN_data_assign() {
	double S_base = 100;			// MW
	double V_base = 12.66;		// kV
	Sbase = S_base;		// Value assignment for attributes of Class AllData 
	Vbase = V_base;
	double X_base = V_base * V_base / S_base;		
	// DLine	
	vector<vector<int>> line_node_pair = { {1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},{15,16},{16,17},{17,18},{2,19},{19,20},{20,21},{21,22},{3,23},{23,24},{24,25},{6,26},{26,27},{27,28},{28,29},{29,30},{30,31},{31,32},{32,33},{8,21},{9,15},{12,22},{18,33},{25,29} };
	vector<double> line_R = { 0.0922,0.4930,0.3660,0.3811,0.8190,0.1872,0.7114,1.0300,1.0440,0.1966,0.3744,1.4680,0.5416,0.5910,0.7463,1.2890,0.7320,0.1640,1.5042,0.4095,0.7089,0.4512,0.8980,0.8960,0.2030,0.2842,1.0590,0.8042,0.5075,0.9744,0.3105,0.3410,2.0000,2.0000,2.0000,0.5000,0.5000 };
	vector<double> line_X = { 0.0470,0.2511,0.1864,0.1941,0.7070,0.6188,0.2351,0.7400,0.7400,0.0650,0.1238,1.1550,0.7129,0.5260,0.5450,1.7210,0.5740,0.1565,1.3554,0.4784,0.9373,0.3083,0.7091,0.7011,0.1034,0.1447,0.9337,0.7006,0.2585,0.9630,0.3619,0.5302,2.0000,2.0000,2.0000,0.5000,0.5000 };// ohm
	int line_num = line_node_pair.size();																																																																								   // R/X标幺化
	for (size_t i_l = 0; i_l < line_num; ++i_l) {
		line_R[i_l] = line_R[i_l] / X_base;
		line_X[i_l] = line_X[i_l] / X_base;
	}
	vector<double> line_S_max(line_num, 1);		
	// Pole data
	vector<int>line_pole_number = { 5, 8, 8, 8, 6, 9, 5, 8, 5, 9, 5, 5, 5, 8, 3, 4, 8, 9, 6, 4, 10, 9, 7, 6, 7, 4, 7, 7, 6, 4, 7, 9, 6, 6, 10, 9, 6 };
	vector<double> pole_lambda_1(line_num, 0.00005);
	vector<double> pole_lambda_2(line_num, 0.04);
	// DNode
	vector<double> node_Pl = { 0, 100, 90, 120, 60, 60, 200, 200, 60, 60, 45, 60, 60	, 120	, 60, 60	, 60, 90, 90, 90, 90, 90, 90, 420, 420, 60, 60, 60, 120, 200, 150, 210, 60 };	// kW
	vector<double> node_Ql = { 0, 60, 40, 80, 30, 20, 100, 100, 20, 20, 30, 35, 35, 80, 10, 20, 20, 40, 40, 40, 40, 40, 50, 200, 200, 25, 25, 20, 70, 600, 70, 100, 40 };			// Load Q, kVar
	int node_num = node_Pl.size();
	// P/Q标幺化
	for (size_t i_n = 0; i_n < node_num; ++i_n) {
		node_Pl[i_n] = node_Pl[i_n] / 1000 / S_base;	
		node_Ql[i_n] = node_Ql[i_n] / 1000 / S_base;
	}
	vector<double> node_V_min(node_num, 0.9);
	vector<double> node_V_max(node_num, 1.1);
	vector<double> node_factor(node_num, 0.9);
	vector<double> node_per_value = { 9, 2, 2, 8, 7, 5, 3, 2, 2, 4, 10, 3, 5, 6, 9, 9, 2, 8, 3, 4, 7, 8, 2, 5, 5, 2, 8, 4, 6, 6, 6, 9, 7 };		// $/kWh 
	// DG
	vector<int> dgNode = { 3,26 };
	vector<double> dgPMax = { 500,500 }; // kW
	vector<double> dgQMax = { 500,500 }; // kVar
	// dgP/dgQ标幺化
	for (size_t i_dg = 0; i_dg < dgPMax.size(); ++i_dg) {
		dgPMax[i_dg] = dgPMax[i_dg] / 1000.0 / S_base;		
		dgQMax[i_dg] = dgQMax[i_dg] / 1000.0 / S_base;
	}
}

void AllData::DHN_data_assign() {
	// -------------算例参数---------------------------------
	double S_base = 100;			// MW
	// H2CHP Parameter
	vector<int> hChpNode = { 7, 12, 20, 24, 29 };
	vector<double> hResidual = { 3360,3360,3360,3360,3360 };	// 100kg H2 -- 3360 kWh
	vector<double> hChpPMax = { 600, 600, 600, 600, 600 };
	vector<double> hChpPMin = { 100, 100, 100, 100, 100 };
	vector<double> etaChpP = { 0.4, 0.4, 0.4, 0.4, 0.4 };
	vector<double> etaChpH = { 0.4, 0.4, 0.4, 0.4, 0.4 };
	vector<double> sigmaChp = { 1.2,1.2,1.2,1.2,1.2 };						// Raio of heat to power. Be cautious
	// ESU Parameter
	vector<double> etaEsuCha = { 0.98, 0.98,0.98,0.98,0.98 };
	vector<double> etaEsuDis = { 0.98, 0.98,0.98,0.98,0.98 };
	vector<double> lbdEsu = { 0.01, 0.01, 0.01, 0.01, 0.01 };
	vector<double> capEsuMax = { 200,200,200,200,200 };		// kWh  REVISED
	vector<double> capEsu0 = { 100,100,100,100,100 };			// kWh
	vector<double> E_pc_min = { 0,0,0,0,0 };			// kW
	vector<double> E_pc_max = { 200,200,200,200,200 };			// kW
	vector<double> E_pd_min = { 0,0,0,0,0 };			// kW
	vector<double> E_pd_max = { 200,200,200,200,200 };			// kW
	// TSU Parameter
	vector<double> etaTsuCha = { 0.95, 0.95,0.95,0.95,0.95 };
	vector<double> etaTsuDis = { 0.95, 0.95,0.95,0.95,0.95 };
	vector<double> lbdTsu = { 0.01, 0.01, 0.01, 0.01, 0.01 };
	vector<double> capTsuMax = { 800,800,800,800,800 };		// kWh  REVISED
	vector<double> capTsu0 = { 400,400,400,400,400 };					// kWh
	vector<double> H_pc_min = { 0,0,0,0,0 };			// kW
	vector<double> H_pc_max = { 800,800,800,800,800 };			// kW
	vector<double> H_pd_min = { 0,0,0,0,0 };			// kW
	vector<double> H_pd_max = { 800,800,800,800,800 };			// kW
	vector<double> h_load_base = { 400, 550, 425, 600, 450 };			// kW
	// Refueler // 33.6 kWh/kg
	vector<double> refuelerCap(5, 33600);
}

