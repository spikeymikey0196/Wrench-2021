#include "HTTPTexture.h"
#include "happyhttp.h"
#include <thread>
#include <vector>
#include <fstream>

using namespace std;

#define Thread  __declspec( thread )

namespace Wrench
{
	Thread int count = 0;
	Thread unsigned char *data = NULL;

	void OnBegin(const happyhttp::Response* r, void* userdata)
	{
		printf("BEGIN (%d %s)\n", r->getstatus(), r->getreason());
		count = 0;
	}

	void OnData(const happyhttp::Response* r, void* userdata, const unsigned char* d, int n)
	{
		//fwrite(data, 1, n, stdout);

		//realloc data
		data = (unsigned char *)realloc((void*)data, count + n);
		memcpy((void*)&data[count], &d[0], n);

		count += n;
	}

	void OnComplete(const happyhttp::Response* r, void* userdata)
	{
		printf("COMPLETE (%d bytes)\n", count);
	}

	Texture *Download(HTTPTexture *caller, const char *domain, const char *filename, const char *saveLocation)
	{
		happyhttp::Connection conn(domain, 80);
		conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

		conn.request("GET", filename, 0, 0, 0);

		while (conn.outstanding())
			conn.pump();

		ofstream f;
		f.open(saveLocation, ios::binary);
		f.write((const char*)data, count);
		f.close();

		delete[] data;

		return new Texture(saveLocation);
	}


	HTTPTexture::HTTPTexture(const char *domain, const char *filename, const char *saveLocation)
	{
		downloadedTexture = NULL;

		//begin download etc here
		download = async(Download, this, domain, filename, saveLocation);
	};

	void HTTPTexture::Bind()
	{
		if (downloadedTexture) downloadedTexture->Bind();
		else
		{
			Texture::Missing()->Bind();
		}
	};

	void HTTPTexture::Bind(int channel)
	{
		if (downloadedTexture) downloadedTexture->Bind(channel);
		else
		{
			Texture::Missing()->Bind(channel);
		}
	};

	void HTTPTexture::Unbind()
	{
		if (downloadedTexture) downloadedTexture->Unbind();
		else
		{
			Texture::Missing()->Unbind();
		}
	};

	void HTTPTexture::Unbind(int channel)
	{
		if (downloadedTexture) downloadedTexture->Unbind(channel);
		else
		{
			Texture::Missing()->Unbind(channel);
		}
	};

	float HTTPTexture::Width()
	{
		if (downloadedTexture) return downloadedTexture->Width();
		else
		{
			if (download.wait_for(chrono::milliseconds(0)) == future_status::ready)
			{
				downloadedTexture = download.get();
				return downloadedTexture->Width();
			}
		}

		return Texture::Missing()->Width();
	};

	float HTTPTexture::Height()
	{
		if (downloadedTexture) return downloadedTexture->Height();
		else
		{
			if (download.wait_for(chrono::milliseconds(0)) == future_status::ready)
			{
				downloadedTexture = download.get();
				return downloadedTexture->Height();
			}
		}

		return Texture::Missing()->Height();
	};

	float HTTPTexture::PixelWidth()
	{
		if (downloadedTexture) return downloadedTexture->PixelWidth();
		else
		{
			if (download.wait_for(chrono::milliseconds(0)) == future_status::ready)
			{
				downloadedTexture = download.get();
				return downloadedTexture->PixelWidth();
			}
		}

		return Texture::Missing()->PixelWidth();
	};

	float HTTPTexture::PixelHeight()
	{
		if (downloadedTexture) return downloadedTexture->PixelHeight();
		else
		{
			if (download.wait_for(chrono::milliseconds(0)) == future_status::ready)
			{
				downloadedTexture = download.get();
				return downloadedTexture->PixelHeight();
			}
		}

		return Texture::Missing()->PixelHeight();
	};

}
