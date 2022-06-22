using Printf

root = "../resources/results/2022-06-07/18-40-18/BGA4/"

for i in 1:24
    d_path = @sprintf "%s%i/" root i
    contents =  readdir(d_path)

    for item in contents
        temp_path = d_path * item
        if isdir(temp_path)
            temp_path = temp_path * "/"
            docs = readdir(temp_path)
            for doc in docs
                mv(temp_path * doc, d_path * doc)
            end
            rm(temp_path)
        end
    end
end