#include <iostream>
#include <array>
#include "stringutils.h"
#include "httputils.h"

struct video
{
	std::string title;
	std::string uploader;
	std::string length;
	std::string view;
	std::string uploaded;
	std::string video_id;
};

int main()
{
	std::array<video, 5> videos;

	std::cout << "Search for: ";
	std::string input;
	getline(std::cin, input);
	std::replace(input.begin(), input.end(), ' ', '+');

	std::string search_url = "https://www.youtube.com/results?search_query=";
	search_url.append(input);
	std::string search_page = get_content(search_url.c_str());

	const char before[] = "\"title\":{\"runs\":[";
	const char after[] = "\",\"params\":";
	unsigned int start;
	unsigned int end;
	std::string all_video_data;

	for (int i = 0; i < 5; i++)
	{
		start = search_page.find(before);
		start += strlen(before);
		end = search_page.find(after, start);
		all_video_data = search_page.substr(start, end - start);

		videos.at(i).title = give_text_between(&all_video_data, "{\"label\":\"", " by");
		videos.at(i).uploader = give_text_between(&all_video_data, "{\"runs\":[{\"text\":\"", "\"");
		videos.at(i).length = give_text_between(&all_video_data, "\"}},\"simpleText\":\"", "\"");
		videos.at(i).view = give_text_between(&all_video_data, "viewCountText\":{\"simpleText\":\"", " ");
		videos.at(i).uploaded = give_text_between(&all_video_data, "\"publishedTimeText\":{\"simpleText\":\"", "\"");
		videos.at(i).video_id = give_text_between(&all_video_data, "videoId\":\"", "\"");

		search_page = search_page.substr(end);

		printf("\n%d %s\nUploader: %s\nVideo length: %s\nViews: %s\nUploaded: %s\n--------------------------------", i, videos.at(i).title.c_str(), videos.at(i).uploader.c_str(), videos.at(i).length.c_str(), videos.at(i).view.c_str(), videos.at(i).uploaded.c_str());
	}

	int selected_music;
	std::cout << "\n\nPlease select the music by number: ";
	std::cin >> selected_music;

	std::cout << "\nPlaying " << videos.at(selected_music).title.c_str() << " by " << videos.at(selected_music).uploader.c_str() << "\n" << std::endl;
	char syscall_buffer[1024];
	sprintf(syscall_buffer, "vlc -I rc \"https://www.youtube.com/watch?v=%s\" --no-video", videos.at(selected_music).video_id.c_str());
	system(syscall_buffer);

	return EXIT_SUCCESS;
}
