#include "stdafx.h"
#include "LanguageManager.h"

typedef std::list<Translation> lT;
typedef std::initializer_list<Translation> inT;
typedef enumLanguagesCodes eLC;
typedef Translation Tr;


LanguageManager::LanguageManager(enumLanguagesCodes code)
	: lang(code)
{
	hashMap.insert(make_pair("Exit", lT(inT({ Tr(eLC::PL,L"Wyjście"), Tr(eLC::EN,L"Exit") }))));
	hashMap.insert(make_pair("Play", lT(inT({ Tr(eLC::PL,L"Graj"), Tr(eLC::EN,L"Play") }))));
	hashMap.insert(make_pair("Options", lT(inT({ Tr(eLC::PL,L"Opcje"), Tr(eLC::EN,L"Options") }))));
	hashMap.insert(make_pair("Credits", lT(inT({ Tr(eLC::PL,L"Autorzy"), Tr(eLC::EN,L"Credits") }))));
	hashMap.insert(make_pair("Solo Game", lT(inT({ Tr(eLC::PL,L"Gra jednoosobowa"), Tr(eLC::EN,L"Solo Game") }))));
	hashMap.insert(make_pair("Player vs Player", lT(inT({ Tr(eLC::PL,L"Gra dwuosobowa"), Tr(eLC::EN,L"Player vs Player") }))));
	hashMap.insert(make_pair("Back", lT(inT({ Tr(eLC::PL,L"Powrót"), Tr(eLC::EN,L"Back") }))));
	hashMap.insert(make_pair("General", lT(inT({ Tr(eLC::PL,L"Ogólne"), Tr(eLC::EN,L"General") }))));
	hashMap.insert(make_pair("Graphics", lT(inT({ Tr(eLC::PL,L"Grafika"), Tr(eLC::EN,L"Graphics") }))));
	hashMap.insert(make_pair("Sound", lT(inT({ Tr(eLC::PL,L"Dźwięk"), Tr(eLC::EN,L"Sound") }))));
	hashMap.insert(make_pair("Choose map size", lT(inT({ Tr(eLC::PL,L"Wybierz rozmiar mapy"), Tr(eLC::EN,L"Choose map size") }))));
	hashMap.insert(make_pair("Choose difficulty level", lT(inT({ Tr(eLC::PL,L"Wybierz poziom trudności"), Tr(eLC::EN,L"Choose difficulty level") }))));
	hashMap.insert(make_pair("Easy", lT(inT({ Tr(eLC::PL,L"Łatwy"), Tr(eLC::EN,L"Easy") }))));
	hashMap.insert(make_pair("Medium", lT(inT({ Tr(eLC::PL,L"Średni"), Tr(eLC::EN,L"Medium") }))));
	hashMap.insert(make_pair("Hard", lT(inT({ Tr(eLC::PL,L"Trudny"), Tr(eLC::EN,L"Hard") }))));
	hashMap.insert(make_pair("Apply changes", lT(inT({ Tr(eLC::PL,L"Zatwierdź"), Tr(eLC::EN,L"Apply changes") }))));
	hashMap.insert(make_pair("Load defaults", lT(inT({ Tr(eLC::PL,L"Ustawienia domyślne"), Tr(eLC::EN,L"Load defaults") }))));
	hashMap.insert(make_pair("Resolution", lT(inT({ Tr(eLC::PL,L"Rozdzielczość"), Tr(eLC::EN,L"Resolution") }))));

	hashMap.insert(make_pair("Vertical Sync", lT(inT({ Tr(eLC::PL,L"Synchronizacja pionowa"), Tr(eLC::EN,L"Vertical sync") }))));
	hashMap.insert(make_pair("Full Screen", lT(inT({ Tr(eLC::PL,L"Tryb pełnoekranowy"), Tr(eLC::EN,L"Full screen") }))));
	hashMap.insert(make_pair("Resolution Scale", lT(inT({ Tr(eLC::PL,L"Skalowanie rozdzielczości"), Tr(eLC::EN,L"Resolution scale") }))));
	hashMap.insert(make_pair("Antialiasing", lT(inT({ Tr(eLC::PL,L"Wygładzanie krawędzi"), Tr(eLC::EN,L"Antialiasing") }))));
	hashMap.insert(make_pair("Yes", lT(inT({ Tr(eLC::PL,L"Tak"), Tr(eLC::EN,L"Yes") }))));
	hashMap.insert(make_pair("No", lT(inT({ Tr(eLC::PL,L"Nie"), Tr(eLC::EN,L"No") }))));

	hashMap.insert(make_pair("What do you want to do", lT(inT({ Tr(eLC::PL,L"Co masz zamiar zrobić"), Tr(eLC::EN,L"What do you want to do") }))));
	hashMap.insert(make_pair("Resume", lT(inT({ Tr(eLC::PL,L"Kontynuuj"), Tr(eLC::EN,L"Resume") }))));
	hashMap.insert(make_pair("Return to Main Menu", lT(inT({ Tr(eLC::PL,L"Wróć do Menu"), Tr(eLC::EN,L"Return to Main Menu") }))));
	hashMap.insert(make_pair("Quit the game", lT(inT({ Tr(eLC::PL,L"Wyjdź z gry"), Tr(eLC::EN,L"Quit the game") }))));
	hashMap.insert(make_pair("Loading", lT(inT({ Tr(eLC::PL,L"Ładowanie"), Tr(eLC::EN,L"Loading") }))));
	hashMap.insert(make_pair("Do you wish to save changes", lT(inT({ Tr(eLC::PL,L"Czy chcesz zapisać zmiany"), Tr(eLC::EN,L"Do you wish to save changes") }))));
	hashMap.insert(make_pair("Language", lT(inT({ Tr(eLC::PL,L"Język"), Tr(eLC::EN,L"Language") }))));

	hashMap.insert(make_pair("you still have to destroy following ships", lT(inT({ Tr(eLC::PL,L"musisz jeszcze zniszczyć poniższe statki"), Tr(eLC::EN,L"you still have to destroy following ships") }))));
	hashMap.insert(make_pair("Please set up your ships", lT(inT({ Tr(eLC::PL,L"ustaw swoje statki"), Tr(eLC::EN,L"please set up your ships") }))));
	hashMap.insert(make_pair("is setting his ships", lT(inT({ Tr(eLC::PL,L"ustawia swoje statki"), Tr(eLC::EN,L"is setting his ships") }))));
	hashMap.insert(make_pair("Menu desing", lT(inT({ Tr(eLC::PL,L"Wygląd menu"), Tr(eLC::EN,L"Menu desing") }))));
	hashMap.insert(make_pair("Game time", lT(inT({ Tr(eLC::PL,L"Czas gry"), Tr(eLC::EN,L"Game time") }))));
	hashMap.insert(make_pair("Rating of players", lT(inT({ Tr(eLC::PL,L"Ocena graczy"), Tr(eLC::EN,L"Rating of players") }))));
	hashMap.insert(make_pair("Statistics", lT(inT({ Tr(eLC::PL,L"Statystyki"), Tr(eLC::EN,L"Statistics") }))));

	hashMap.insert(make_pair("Total number of shots", lT(inT({ Tr(eLC::PL,L"Całkowita liczba strzałów"), Tr(eLC::EN,L"Total number of shots") }))));
	hashMap.insert(make_pair("Total number of hits", lT(inT({ Tr(eLC::PL,L"Całkowita liczba trafień"), Tr(eLC::EN,L"Total number of hits") }))));
	hashMap.insert(make_pair("Accuracy", lT(inT({ Tr(eLC::PL,L"Celność"), Tr(eLC::EN,L"Accuracy") }))));
	hashMap.insert(make_pair("The biggest hit series", lT(inT({ Tr(eLC::PL,L"Największa seria trafień"), Tr(eLC::EN,L"The biggest hit series") }))));
	hashMap.insert(make_pair("The biggest miss series", lT(inT({ Tr(eLC::PL,L"Największa seria chybień"), Tr(eLC::EN,L"The biggest miss series") }))));
	hashMap.insert(make_pair("has won the game", lT(inT({ Tr(eLC::PL,L"wygrał grę"), Tr(eLC::EN,L"has won the game") }))));

	hashMap.insert(make_pair("Press left mouse button to place the ship", lT(inT({ Tr(eLC::PL,L"Naciśnij lewy przycisk myszy aby ustawić statek"), Tr(eLC::EN,L"Press left mouse button to place the ship") }))));
	hashMap.insert(make_pair("Press right mouse button to rotate the ship", lT(inT({ Tr(eLC::PL,L"Naciśnij prawy przycisk myszy aby obrócić statek"), Tr(eLC::EN,L"Press right mouse button to rotate the ship") }))));

	hashMap.insert(make_pair("First player name", lT(inT({ Tr(eLC::PL,L"Nazwa pierwszego gracza"), Tr(eLC::EN,L"First player name") }))));
	hashMap.insert(make_pair("Second player name", lT(inT({ Tr(eLC::PL,L"Nazwa drugiego gracza"), Tr(eLC::EN,L"Second player name") }))));
	hashMap.insert(make_pair("AI", lT(inT({ Tr(eLC::PL,L"AI"), Tr(eLC::EN,L"AI") }))));

	hashMap.insert(make_pair("Main Menu volume", lT(inT({ Tr(eLC::PL,L"Głośność w Menu Głównym"), Tr(eLC::EN,L"Main Menu volume") }))));
	hashMap.insert(make_pair("In game volume", lT(inT({ Tr(eLC::PL,L"Głośność w grze"), Tr(eLC::EN,L"In game volume") }))));
	hashMap.insert(make_pair("Effects volume", lT(inT({ Tr(eLC::PL,L"Głośność efektów specjalnych"), Tr(eLC::EN,L"Effects volume") }))));
}

std::wstring LanguageManager::getText(const std::string & code) const
{
	const std::list<Translation>*  translations = nullptr;
	try {
		translations = &hashMap.at(code);
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of range error: " << oor.what() << "when tried to get key: " << code << '\n';
	}
	
	if(translations!=nullptr)
		for (auto translation = translations->begin(); translation != translations->end(); ++translation)
		{
			if (translation->getLanguageCode() == lang)
			{
				return translation->getTranslation();
			}
		}
	return std::wstring();
}

