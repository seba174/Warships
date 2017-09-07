#include "LanguageManager.h"
#include <iostream>
using std::list;
using std::string;
using std::initializer_list;





LanguageManager::LanguageManager(enumLanguagesCodes code)
	: lang(code)
{
	hashMap.insert(std::make_pair("Exit", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Wyjście"), Translation(enumLanguagesCodes::EN,L"Exit") }))));
	hashMap.insert(std::make_pair("Play", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Graj"), Translation(enumLanguagesCodes::EN,L"Play") }))));
	hashMap.insert(std::make_pair("Options", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Opcje"), Translation(enumLanguagesCodes::EN,L"Options") }))));
	hashMap.insert(std::make_pair("Credits", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Autorzy"), Translation(enumLanguagesCodes::EN,L"Credits") }))));
	hashMap.insert(std::make_pair("Solo Game", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Gra jednoosobowa"), Translation(enumLanguagesCodes::EN,L"Solo Game") }))));
	hashMap.insert(std::make_pair("Player vs Player", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Gra dwuosobowa"), Translation(enumLanguagesCodes::EN,L"Player vs Player") }))));
	hashMap.insert(std::make_pair("Back", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Powrót"), Translation(enumLanguagesCodes::EN,L"Back") }))));
	hashMap.insert(std::make_pair("General", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Ogólne"), Translation(enumLanguagesCodes::EN,L"General") }))));
	hashMap.insert(std::make_pair("Graphics", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Grafika"), Translation(enumLanguagesCodes::EN,L"Graphics") }))));
	hashMap.insert(std::make_pair("Sound", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Dźwięk"), Translation(enumLanguagesCodes::EN,L"Sound") }))));
	hashMap.insert(std::make_pair("Choose map size", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Wybierz rozmiar mapy"), Translation(enumLanguagesCodes::EN,L"Choose map size") }))));
	hashMap.insert(std::make_pair("Choose difficulty level", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Wybierz poziom trudności"), Translation(enumLanguagesCodes::EN,L"Choose difficulty level") }))));
	hashMap.insert(std::make_pair("Easy", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Łatwy"), Translation(enumLanguagesCodes::EN,L"Easy") }))));
	hashMap.insert(std::make_pair("Medium", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Średni"), Translation(enumLanguagesCodes::EN,L"Medium") }))));
	hashMap.insert(std::make_pair("Hard", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Trudny"), Translation(enumLanguagesCodes::EN,L"Hard") }))));
	hashMap.insert(std::make_pair("Apply changes", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Zatwierdź"), Translation(enumLanguagesCodes::EN,L"Apply changes") }))));
	hashMap.insert(std::make_pair("Load defaults", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Ustawienia domyślne"), Translation(enumLanguagesCodes::EN,L"Load defaults") }))));
	hashMap.insert(std::make_pair("Resolution", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Rozdzielczość"), Translation(enumLanguagesCodes::EN,L"Resolution") }))));
	
	hashMap.insert(std::make_pair("Vertical Sync", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Synchronizacja pionowa"), Translation(enumLanguagesCodes::EN,L"Vertical sync") }))));
	hashMap.insert(std::make_pair("Full Screen", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Tryb pełnoekranowy"), Translation(enumLanguagesCodes::EN,L"Full screen") }))));
	hashMap.insert(std::make_pair("Resolution Scale", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Skalowanie rozdzielczości"), Translation(enumLanguagesCodes::EN,L"Resolution scale") }))));
	hashMap.insert(std::make_pair("Antialiasing", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Wygładzanie krawędzi"), Translation(enumLanguagesCodes::EN,L"Antialiasing") }))));
	hashMap.insert(std::make_pair("Yes", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Tak"), Translation(enumLanguagesCodes::EN,L"Yes") }))));
	hashMap.insert(std::make_pair("No", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Nie"), Translation(enumLanguagesCodes::EN,L"No") }))));

	hashMap.insert(std::make_pair("What do you want to do", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Co masz zamiar zrobić"), Translation(enumLanguagesCodes::EN,L"What do you want to do") }))));
	hashMap.insert(std::make_pair("Resume", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Kontynuuj"), Translation(enumLanguagesCodes::EN,L"Resume") }))));
	hashMap.insert(std::make_pair("Return to Main Menu", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Wróć do menu"), Translation(enumLanguagesCodes::EN,L"Return to Main Menu") }))));
	hashMap.insert(std::make_pair("Quit the game", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Wyjdź z gry"), Translation(enumLanguagesCodes::EN,L"Quit the game") }))));
	hashMap.insert(std::make_pair("Loading", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Ładowanie"), Translation(enumLanguagesCodes::EN,L"Loading") }))));
	hashMap.insert(std::make_pair("Do you wish to save changes", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Czy chcesz zapisać zmiany"), Translation(enumLanguagesCodes::EN,L"Do you wish to save changes") }))));
	hashMap.insert(std::make_pair("Language", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Język"), Translation(enumLanguagesCodes::EN,L"Language") }))));

	hashMap.insert(std::make_pair("you still have to destroy following ships", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"musisz jeszcze zniszczyć poniższe statki"), Translation(enumLanguagesCodes::EN,L"you still have to destroy following ships") }))));
	hashMap.insert(std::make_pair("Please set up your ships", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"ustaw swoje statki"), Translation(enumLanguagesCodes::EN,L"please set up your ships") }))));
	hashMap.insert(std::make_pair("Menu desing", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Wygląd menu"), Translation(enumLanguagesCodes::EN,L"Menu desing") }))));
	hashMap.insert(std::make_pair("Game time", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Czas gry"), Translation(enumLanguagesCodes::EN,L"Game time") }))));
	hashMap.insert(std::make_pair("Rating of players", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Ocena graczy"), Translation(enumLanguagesCodes::EN,L"Rating of players") }))));
	hashMap.insert(std::make_pair("Statistics", std::list<Translation>(initializer_list<Translation>({ Translation(enumLanguagesCodes::PL,L"Statystyki"), Translation(enumLanguagesCodes::EN,L"Statistics") }))));
	
	


}

std::wstring LanguageManager::getText(const std::string & code) 
{
	std::list<Translation>&  translations = hashMap[code];
	for (auto translation = translations.begin();translation != translations.end(); ++translation)
	{
		if (translation->getLanguageCode() == lang)
		{	
			return translation->getTranslation();
		}
	}
	return std::wstring();
}

