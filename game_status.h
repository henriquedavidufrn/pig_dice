namespace gs{
	struct GameState
	{

		using names = std::string;
		typedef size_t face_t;
		typedef size_t seed_t;

		enum class seed_type_e : short int { RANDOM = 0, CLIENT_DEFINED};

		pl::Player player1;
		pl::Player player2;

		pd::Dice dice;

		pt::Pontos pontos_game;

		gm::Estado estado_game;


		int state_game = -1;	// 0 - Inicia | 1 - Jogador 1 | 2 - Jogador 2 | 3 - Game Over
		

		// Recebe qual o estado atual do jogo
		void stateGame(){

			int pontA, pontB;

			pontA = pontos_game.getPont_J1();
			pontB = pontos_game.getPont_J2();

			if(pontA < 100 && pontB < 100){
				state_game = 1;
			} else{
				state_game = 3;
			}

		}

		// Modifica o estado do jogo
		void changeState( int estado_muda ){
			state_game = estado_muda;
		}

		// Adiciona pontos a um determinado jogador
		void addPoints(pl::Player &pl, int ponto){
			pontos_game.addPoint(pl, ponto);
		}

		// Adiciona os pontos de cada rodada de todos os 2 jogadores
		/*void add_pontos_all(int p1, int p2){
			pontos_game.setPontos(p1, p2);
		}*/

		// Joga o dado.
		int rollDice(){
			return dice.roll();
		}

		// Muda o jogador.
		void passUser(){
			names jog = estado_game.getJogador();

			if(jog == player1.getNome())
				estado_game.setJogador( player2 );
			else
				estado_game.setJogador( player1 );


		}

		// Atribui uma ação, rolar ou passar a vez.
		void action_Game( std::string acao ){
			if(acao == "Roll"){
				int value = rollDice();

				std::cout << "Valor : " << value << std::endl;
				auto nomeJogador = estado_game.getJogador();

				if(nomeJogador == player1.getNome()){
					player1.addPontuacao(value);
				} else{
					player2.addPontuacao(value);
				}

				if(value == 1){
					
					player1.setPontuacao(0);
					player2.setPontuacao(0);
					passUser();
				}

			} else if( acao == "Hold") {

				passUser();

			} else{
				std::cout << "\nA ação não é válida!" << std::endl;
				std::cout <<"Roll or Hold ?" << std::endl;
				std::string valor;
				std::cin >> valor;
				action_Game(valor);
			}
		}

	};
}