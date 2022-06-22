using GLMakie, Printf


struct Point
    x::Float64
    y::Float64
end

function read_in_points(path::String)::Vector{Point}
    points = Point[]
    open(path, "r") do io
        
        while ! eof(io)
            line = readline(io)
            temp = split(line, ", ")
            push!(points, Point(parse(Float64, temp[1]), parse(Float64, temp[2])))
            
        end
    end

    return points
end
# set_window_config!(;
#     renderloop = renderloop,
#     vsync = false,
#     framerate = 30.0,
#     float = false,
#     pause_rendering = false,
#     focus_on_show = false,
#     decorated = true,
#     title = "Makie"
# )

function main()
    path = "./circ200.txt"
    points = read_in_points(path)
    @printf("%f, %f\n", points[199].x, points[199].y)
    f = Figure()
    Axis(f[1, 1])

    xs = Vector{Float64}()
    ys = Vector{Float64}()

    for point in points
        push!(xs, point.x)
        push!(ys, point.y)
    end

    scatter!(xs, ys, color = :red)
    # scatterlines!(xs, ys .* 3, color = xs, markercolor = :blue)

    f
end

main()