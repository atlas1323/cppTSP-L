

open("circ100.txt", "a") do io
    step = π/100
    for α in 0:step:2π
        line = "" * string(trunc(cos(α), digits=4)) * ", " * string(trunc(sin(α), digits=4)) * "\n"
        # println(trunc(cos(α), digits=4),", ", trunc(sin(α), digits=4))
        write(io, line)
    end 
end