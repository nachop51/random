import json
import requests
from bs4 import BeautifulSoup
import lxml


def load_credentials():
    """The file must contain a JSON object with the following structure:
    {
        "headers": {
            "User-Agent": "your_user_agent"
        },
        "cookies": {
            "cookie_name": "cookie_value"
        }
    }
    """
    with open("account.json") as f:
        return json.load(f)


def make_request(url):
    credentials = load_credentials()

    res = requests.get(
        url, headers=credentials["headers"], cookies=credentials["cookies"]
    )

    return res


def scrap_the_shit_out_of_the_page(html: str):
    soup = BeautifulSoup(html, "lxml")


def main():
    url = input("Enter the URL: ")

    res = make_request(url)

    data = scrap_the_shit_out_of_the_page(res.text)

    print(data)


if __name__ == "__main__":
    main()
