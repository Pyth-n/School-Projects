// Search Engine for music brainz

// This jQuery allows the use of music brainz API

var currentBrainzSearch;
var nextPageToken = "";
var song_amount;
var addID;
var localInc;
var localSto;
var recentYTQuery;

// Getting local key
if (localStorage.getItem(0) === null) {
	localInc = 0;
	console.log("EMPY");
} else {
	localInc = localStorage.length;
	console.log(localStorage.getItem(0));
}

// jQuery is used for submit buttons instead of having onClick buttons and to have images
// for submit buttons
$(document).ready(function() {
	initSearch();
	$("#search-music").submit(function(event) {
		addID = 0;
		document.getElementById('search-button').style.animation = "rotation 4s linear";
		loadAnimationShow();
		run_search(0);
		window.setTimeout(loadAnimationHide, 3000);
		event.preventDefault();
	});
});

function initFavorites(){
	document.getElementById('search-container').style.display = 'none';
	document.getElementById('favorite-container').style.display = 'block';
	document.getElementById('about-container').style.display = 'none';
	populateFaves();
}

function initSearch() {
	document.getElementById('search-container').style.display = 'block';
	// transition view
	document.getElementById('search-container').style.visibility = 'visible';
	document.getElementById('search-container').style.opacity = 1;
	document.getElementById('favorite-container').style.display = 'none';
	document.getElementById('about-container').style.display = 'none';
}

function initAbout()
{
	document.getElementById('search-container').style.display = 'none';
	document.getElementById('favorite-container').style.display = 'none';
	document.getElementById('about-container').style.display = 'block';
}

function populateFaves() {
	for (var i = 0; i < localStorage.length - 1; i++) {
		// Object that is parsed
		var details = JSON.parse(localStorage.getItem(localStorage.key(i)));

	{
		var div = document.createElement("div");
		div.setAttribute("class", "favorite-item");
		var song = document.createTextNode(details.song);
		div.appendChild(song);
		document.getElementById('favorite-info').appendChild(div);
	}
	{
		var div = document.createElement("div");
		div.setAttribute("class", "favorite-item");
		var artist = document.createTextNode(details.artist);
		div.appendChild(artist);
		document.getElementById('favorite-info').appendChild(div);
	}
	{
		var div = document.createElement("div");
		div.setAttribute("class", "favorite-item");
		var album = document.createTextNode(details.album);
		div.appendChild(album);
		document.getElementById('favorite-info').appendChild(div);
	}
	{
		var div = document.createElement("div");
		div.setAttribute("class", "favorite-item");
		div.setAttribute("id", localStorage.key(i));
		div.setAttribute("style", "text-align: center;");
		div.setAttribute("onclick", "removeItem(this.id)");
		div.innerHTML = "&#128148;";
		document.getElementById('favorite-info').appendChild(div);
	}

	}
}

function removeItem(i) {
	var item = document.getElementById(i);
	var album = document.getElementById(i).previousSibling;
	var artist = document.getElementById(i).previousSibling.previousSibling;
	var song = document.getElementById(i).previousSibling.previousSibling.previousSibling;
	
	song.parentNode.removeChild(song);
	item.parentNode.removeChild(item);
	album.parentNode.removeChild(album);
	artist.parentNode.removeChild(artist);
	localStorage.removeItem(i);
}

function classIndex(i) {
	var album = document.getElementById(i).previousSibling.innerHTML;
	var artist = document.getElementById(i).previousSibling.previousSibling.innerHTML;
	var song = document.getElementById(i).previousSibling.previousSibling.previousSibling.innerHTML;
	document.getElementById(i).childNodes[0].style.animation = "rotation 1s linear";
	var icon = document.getElementById(i).childNodes[0];
	icon.src = 'imgs/checkmark.png';

	// create song object
	var toSave = {
		song: song,
		artist: artist,
		album: album
	}

	var JSONed = JSON.stringify(toSave);
	localStorage.setItem(localInc++, JSONed);
	console.log(JSONed);
}


function run_search(skip) {
	var song = document.getElementById('song-search').value;
	var artist = document.getElementById('artist-search').value;
	//var country = document.getElementById('country-search').value;

	if (!song) {
		console.log("Song is necessary!");
		return;
	}

	musicBrainzSearch(song, artist, skip);
	var query = song + " " + artist;
	youtubeSearch(query);
}

var loadAnimationShow = function() {
	document.getElementById('loadingCSS').style.visibility = 'visible';
	document.getElementById('loadingCSS').style.display = "block";
}

var loadAnimationHide = function () {
	document.getElementById('results-container-info').style.visibility = 'visible';
	document.getElementById('results-container-info').style.display = 'grid';
	document.getElementById('results-container-info').style.opacity = 1;
	document.getElementById('loadingCSS').style.visibility = 'hidden';
	document.getElementById('loadingCSS').style.display = "none";
	document.getElementById('song-amount').style.visibility = 'visible';
	document.getElementById('song-amount').style.display = 'block';
	document.getElementById('song-amount').style.textAlign = 'center';
	document.getElementById('song-amount').innerHTML = "Found " + song_amount + " songs";
	document.getElementById('youtube-search-results').style.visibility = 'visible';
	document.getElementById('youtube-search-results').style.display = 'grid';
	document.getElementById('more').style.display = "block";
}

var musicBrainzSearch = function(song, artist, skip) {

	var offset = 0;
	var search_query = song;
	var search_description = song;
	var country = "US";

	if (!song) {
		console.log("A song is necessary!");
		return;
	}

	if (country) {
		search_query = search_query + ' AND country:' + country;
	}

	if (artist) {
		search_query = search_query + ' AND artist:' + artist;
	}

	var request = {
		query: search_query,
		fmt: 'json',
		//limit: 5,
		offset: 0
	};

	currentBrainzSearch = $.ajax({
		url: "https://musicbrainz.org/ws/2/recording/",
		data: request,
		type: "GET",
	})
	.done(function(result) {
		song_amount = result.count;
		parseInfo(result);
	});
}

var youtubeSearch = function (query) {
	var request = {
		part: 'snippet',
		key: 'AIzaSyATFOByRDvvLMx1dDK5t-HSKnP1t4YbVvo',
		q: query,
		maxResults: 6,
		pageToken: nextPageToken
	};

	$.ajax({
		url: "https://www.googleapis.com/youtube/v3/search",
		data: request,
		dataType: "jsonp",//use jsonp to avoid cross origin issues
		type: "GET",
		safesearch: 'strict',
		type: 'video',
		videoEmbeddable: true,
	})
	.done(function(result) {
		console.log(result.nextPageToken);
		nextPageToken = result.nextPageToken;
		recentYTQuery = query;

		for (i = 0; i < result.items.length; i++) {
			addFrameTube(result.items[i].id.videoId);
		}
	});

}

var addFrameTube = function(id) {
	var fram = document.createElement('iframe');
	fram.setAttribute("width", "190");
	fram.setAttribute("height", "120");
	fram.setAttribute('src', 'http://www.youtube.com/embed/' + id);
	fram.setAttribute("frameBorder", "0");
	document.getElementById('youtube-container-info').appendChild(fram);
}

function moreVids() {
	youtubeSearch(recentYTQuery);
	loadAnimationShow();
	//run_search(0);
	window.setTimeout(loadAnimationHide, 3000);
}

var parseInfo = function(result) {
	var length = result.recordings.length;
	var title = "No Title"
	var artist = "No Artist"
	var release_set = "No Album"
	var identifier = "no_id";

	for (r = 0; r < length; ++r) {
		if (r in result.recordings) {
			var recording = result.recordings[r];
			title = recording.title;
			artist = recording['artist-credit'][0].artist.name;
			release_set = '';

			if (recording.releases && recording.releases[0].title) {
				release_set = '"' + recording.releases[0].title + '"';
				if (recording.releases.length > 1) {
					var more = recording.releases.length - 1;
					release_set = release_set + " <i>and " + more + " more.</i>"
				}
			}

			identifier = recording.id;

			addToGrid(title, artist, release_set);
		}
	}

	
}

var addToGrid = function(title, artist, album) {

	{
		// title
		var div = document.createElement("div");
		var text = document.createTextNode(title);
		div.setAttribute("class", "info-items");
		div.appendChild(text);
		document.getElementById('results-container-info').appendChild(div);
	}

	{
		// artist
		var div = document.createElement("div");
		var text = document.createTextNode(artist);
		div.setAttribute("class", "info-items");
		div.appendChild(text);
		document.getElementById('results-container-info').appendChild(div);
	}

	{
		// album
		var div = document.createElement("div");
		var text = document.createTextNode(album);
		div.setAttribute("class", "info-items");
		div.appendChild(text);
		document.getElementById('results-container-info').appendChild(div);
	}
	{
		var rootDiv = document.createElement("div");
		rootDiv.setAttribute("class", "info-items");
		rootDiv.setAttribute("id", addID);
		rootDiv.setAttribute("onclick", "classIndex(" + addID++ + ")");
		// heart
		var div = document.createElement("input");
		div.setAttribute("type", "image");
		div.setAttribute("src", "imgs/plus.png");
		div.setAttribute("style", "width:30px;");

		rootDiv.appendChild(div);

		document.getElementById('results-container-info').appendChild(rootDiv);
	}
}

