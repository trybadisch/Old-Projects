from selenium import webdriver
import time

def run_driver(subject):
	options = webdriver.ChromeOptions()
	options.add_argument('--headless')
	options.add_argument('ignore-certificate-errors')
	options.add_argument("--disable-extensions")
	options.add_argument("--whitelisted-ips=''")
	options.add_argument("--no-sandbox")
	driver = webdriver.Chrome('./chromedriver', chrome_options=options)

	driver.get("http://localhost/backend")
	driver.add_cookie({'name' : 'SESSION', 'value' : 'FLAG{7c31058931bf95ef2b723014381f8485}'})
	driver.execute_script("document.write(`"+subject+"`)")
	
	time.sleep(1)
