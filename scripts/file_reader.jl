# let's read in a file
using CairoMakie, Random, Printf

"""
Immutable struct to store points
"""
struct Point
    x::Float64
    y::Float64
end

mutable struct Contender
    evals::Int64
    path_length::Float64
    route::Vector{Int64}

    Contender() = new()
end

mutable struct Experiment
    data_set::String
    run_time::String
    method::String
    data_path::String
    contenders::Vector{Contender}

    Experiment() = new()
end

data_dir = "../resources/datasets/"
f_path = data_dir * "tsp.txt"
exp_dir = "../resources/results/pudding/"
e_path = exp_dir * "tsp_VarP_2022`6`16-0`3`56.txt"
circ_path = "./circ200.txt"


"""
Retrieves data from file described by `path` and returns Vector of points
"""
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

"""
Translates a route into x and y series for plotting
"""
function translate_route(points::Vector{Point}, route::Vector{Int64})
    xs = Vector{Float64}()
    ys = Vector{Float64}()

    for index in route
        push!(xs, points[index].x)
        push!(ys, points[index].y)
    end

    return xs, ys
end


"""
Reads in the results
"""
function get_experiment(path::String)::Experiment
    
    exp = Experiment()
    exp.contenders = Vector{Contender}()
    open(path, "r") do io
        lines = readlines(io)
        # TODO: handle header info
        for (index, line) in enumerate(lines)
            if index == 1
                exp.data_set = split(line, ":\t")[2]
            elseif index == 2
                exp.run_time = split(line, ":\t")[2]
            elseif index == 3
                exp.method = split(line, ":\t")[2]
            elseif index == 5
                exp.data_path = split(line, ":\t")[2]
            elseif index > 8
                contender = Contender()
                parts = split(line, " | ")
                contender.evals = parse(Int64, parts[1])
                contender.path_length = parse(Float64, parts[2])
                route = split(parts[3], " ")
                contender.route = Vector{Int64}()
                for spot in route
                    if spot != " " && spot != ""
                        temp = parse(Int64, spot)
                        push!(contender.route, parse(Int64, spot)+1)
                    end
                end
                push!(exp.contenders, contender)
            end
        end
    end
    return exp
end

function graph_route(xs::Vector{Float64}, ys::Vector{Float64}, f)
    # f = Figure()
    Axis(f[1, 1])

    scatterlines!(xs, ys, color = :red, markersize = 2, linewidth = 1)
    # f
end

function main()
    points = read_in_points(f_path)
    p_size = size(points, 1)
    path = collect(1:p_size)

    # shuffle!(path)

    # display(path)
    # xs,ys = translate_route(points, path)

    experiment = get_experiment(e_path)
    for con in experiment.contenders
        println(con.path_length)
    end
    # println("Figure f")
    # f = Figure(resolution = (800, 800))
    # x2, y2 = translate_route(points, experiment.contenders[1].route)
    # graph_route(x2, y2, f)
    # save("figure1.png", f)
    # f

    # println("Figure g")
    # g = Figure(resolutions = (800, 800))
    # xs, ys = translate_route(points, experiment.contenders[lastindex(experiment.contenders)].route)
    # graph_route(xs, ys, g)   
    # save("figure2.png", g)
    # g

    save_path = "/mnt/c/Users/atlas1323/Desktop/"
    for (index, con) in enumerate(experiment.contenders)
        if index%5 == 0
            f_name = @sprintf "%sImages5/Figure%04i.png" save_path index
            g_title = @sprintf "E: %i | P: %f" con.evals con.path_length
            fig = Figure(resolution = (800, 800))
            Axis(fig[1,1], title=g_title)
            xs, ys = translate_route(points, con.route)
            graph_route(xs, ys, fig)
            save(f_name, fig)
        end
    end
    
end

main()