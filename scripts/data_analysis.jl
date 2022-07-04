using CairoMakie, Random, Distributions, Printf, ColorTypes

# △△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△
# Types
# ▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽

"""
Immutable struct to store points
"""
struct Point
    x::Float64
    y::Float64
end

"""
Contender solution data structure
"""
mutable struct Contender
    evals::Int64
    path_length::Float64
    route::Vector{Int64}

    Contender() = new()
end


"""

"""
mutable struct Experiment
    data_set::String
    run_time::String
    parameters::Dict{String, Any}
    method::String
    data_path::String
    contenders::Vector{Contender}


    Experiment() = new()
end


"""
Experiment parameter string parser
"""
function parse_parameters(param_string::SubString{String})::Dict{String, Any}
    dict = Dict{String, Any}()
    params = split(param_string, " ")
    for p in params
        if ':' in p
            key, val = split(p, ':')
            dict[key] = parse(Float64, val)
        end
    end
    return dict
end


# △△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△
# Data Processing
# ▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽

mutable struct DataPoint
    average::Float64
    stdev::Float64
    evals::Int64
end


# TODO: Cohort struct defintition
mutable struct Cohort
    experiments::Vector{Experiment}
    data_set::String
    data_path::String
    parameters::Dict{String, Any}
    method::String
    step_size::Int64
    data::Vector{DataPoint}
    n::Int64
    
    Cohort() = new()
end

# TODO: Cohort constructor
function build_cohort(directory::String)::Cohort
    # Get all files in directory and collect experiments
    cohort = Cohort()
    exp_list = readdir(directory)
    cohort.n = size(exp_list, 1)
    cohort.experiments = Vector{Experiment}()
    for e in exp_list
        path = @sprintf "%s/%s" directory e
        println(path)
        push!(cohort.experiments, get_experiment(path))
    end
    
    # TODO: Populate other variables
    cohort.data_set = cohort.experiments[1].data_set
    cohort.data_path = cohort.experiments[1].data_path
    cohort.method = cohort.experiments[1].method
    cohort.parameters = cohort.experiments[1].parameters
    cohort.step_size = 1000
    println(cohort.parameters)

    println(typeof(cohort))
    data_calc!(cohort)
    return cohort    
end

function data_calc!(cohort::Cohort)
    counter = fill(1, cohort.n)
    println(cohort.parameters["E"])
    println(cohort.experiments[1].data_set)
    cohort.data = Vector{DataPoint}()
    for i in 1:cohort.step_size:cohort.parameters["E"]
        μ = 0
        σ = 0
        target = i*cohort.step_size
        for j in 1:cohort.n
            # advance counter until it recaches target, then grab 1 before that
            while (target >= cohort.experiments[j].contenders[counter[j]].evals) && (counter[j] < size(cohort.experiments[j].contenders, 1))
                # println(@sprintf "%i :: %i :: %i" target cohort.experiments[j].contenders[counter[j]].evals counter[j])
                counter[j] += 1
            end
            # use determined counter to create average
            μ += cohort.experiments[j].contenders[counter[j]-1].path_length
        end
        μ /= cohort.n
        for j in 1:cohort.n
            σ += (cohort.experiments[j].contenders[counter[j]-1].path_length-μ)^2
        end
        σ = sqrt(σ/cohort.n)
        push!(cohort.data, DataPoint(μ, σ, target))
    end
end

# TODO: Cohort calculatiosn
#   [x] data points averages (at defined intervals)
#   [x] data point stdevs (at defined intervials)
#   [ ] Cohort 
#   [ ] survivability curves calcs




# △△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△
# Data IO
# ▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽

"""
Reads in the results
"""
function get_experiment(path::String)::Experiment
    
    exp = Experiment()
    exp.contenders = Vector{Contender}()
    open(path, "r") do io
        lines = readlines(io)
        # handle header info
        for (index, line) in enumerate(lines)
            if index == 1
                exp.data_set = split(line, ":\t")[2]
            elseif index == 2
                exp.run_time = split(line, ":\t")[2]
            elseif index == 3
                exp.method = split(line, ":\t")[2]
            elseif index == 4
                parse_string = split(line, "\t")[2]
                exp.parameters = parse_parameters(parse_string)
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

# Read in experiment files and store in container of experiments
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



# △△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△
# Graph Factory
# ▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽

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

function graph_route(xs::Vector{Float64}, ys::Vector{Float64}, f, l_col)
    # f = Figure()
    # Axis(f[1, 1])
    Axis(f[1, 1], xscale = log10, title = string("log10"),
        yminorticksvisible = true, yminorgridvisible = true,
        yminorticks = IntervalsBetween(8))

    scatterlines!(xs, ys, color = l_col, markersize = 2, linewidth = 1)
    # f
end

# TODO: Individual Route graph markersize

# TODO: Video maker

# TODO: Efficiency graph

# TODO: 

# △△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△
# Main body and logic flow
# ▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽

function main()
    # test1 = "Params:	P:1000 E:3000000 SR:0.500000"
    # test2 = "Params:	 E:3000000"

    # t1 = split(test1, '\t')[2]
    # println(t1)
    # t2 = split(test2, '\t')[2]
    # println(t2)
    # a = parse_parameters(t1)
    # b = parse_parameters(t2)

    # println(a)
    # println(b)

    dir_path = "../resources/results/2022-06-07/18-40-18/BGA2"
    dir_path2 = "../resources/results/2022-06-07/18-40-18/BGA4/8"
    dir_path3 = "../resources/results/2022-06-07/18-40-18/Random"
    dir_path4 = "../resources/results/2022-06-07/18-40-18/RMHC"
    # cohort = Cohort()
    # println(typeof(cohort))

    cohort = build_cohort(dir_path)
    cohort2 = build_cohort(dir_path2)
    cohort3 = build_cohort(dir_path3)
    cohort4 = build_cohort(dir_path4)


    xs = Vector{Float64}()
    ys = Vector{Float64}()

    for p in cohort.data
        push!(xs, p.evals)
        push!(ys, p.average)
    end

    xs2 = Vector{Float64}()
    ys2 = Vector{Float64}()

    for p in cohort2.data
        push!(xs2, p.evals)
        push!(ys2, p.average)
    end

    xs3 = Vector{Float64}()
    ys3 = Vector{Float64}()

    for p in cohort3.data
        push!(xs3, p.evals)
        push!(ys3, p.average)
    end

    xs4 = Vector{Float64}()
    ys4 = Vector{Float64}()

    for p in cohort4.data
        push!(xs4, p.evals)
        push!(ys4, p.average)
    end

    title = "test.png"
    # fig = Figure(resolution = (800, 800))
    fig = Figure()
    ax = Axis(fig[1, 1], xscale = log10, title = string("log10"),
        yminorticksvisible = true, yminorgridvisible = true,
        yminorticks = IntervalsBetween(8))
    
    scatterlines!(xs, ys, color=:blue, label="BGA2")
    scatterlines!(xs2, ys2, color=:red, label="BGA4-1")
    scatterlines!(xs3, ys3, color=:green, label="Random")
    scatterlines!(xs4, ys4, color=:orange, label="RMHC")

    fig[1, 2] = Legend(fig, ax, "Methods", framevisible=false)

    save(title, fig)
    
    # av_rec = Vector{Float64}()
    # std_rec = Vector{Float64}()

    # title2 = "bga4.png"
    # fig2 = Figure(resolution = (2500, 2500))
    # ax2 = Axis(fig2[1, 1], xscale = log10, title = string("BGA4 Range"),
    # xminorticksvisible = true, xminorgridvisible=true, xminorticks= IntervalsBetween(8),
    # yminorticksvisible = true, yminorgridvisible = true,
    # yminorticks = IntervalsBetween(8))

    # root_path = "../resources/results/2022-06-07/18-40-18/BGA4/"
    # for i in 1:25
    #     # step = i*1/25
    #     r = rand(Uniform(0, 1))
    #     b = rand(Uniform(0, 1))
    #     g = rand(Uniform(0, 1))
    #     rand_col = RGB(r, g, b)
    #     local_path = @sprintf "%s%i" root_path i
    #     # get cohort
    #     local_cohort = build_cohort(local_path)
    #     # collect datasets for graphing
    #     xsv = Vector{Float64}()
    #     ysv = Vector{Float64}()

    #     for p in local_cohort.data
    #         push!(xsv, p.evals)
    #         push!(ysv, p.average)
    #     end

    #     # line_c = RGB(i*step, 255, 255)
    #     lab = @sprintf "BGA4-%i" i
    #     scatterlines!(xsv, ysv, label=lab, color=rand_col)
        
    #     push!(av_rec, local_cohort.data[end].average)
    #     push!(std_rec, local_cohort.data[end].stdev)
        
    # end
    # fig2[1, 2] = Legend(fig2, ax2, "Methods", framevisible=false)


    # for i in 1:25
    #     s = @sprintf "%02i: %f, %f" i av_rec[i] std_rec[i]
    #     println(s)
    # end

    # save(title2, fig2)

    # graph_route(xs2, ys2, fig, :blue)
    # graph_route(xs, ys, fig, :red)
    # graph_route(xs3, ys3, fig, :green)
    # graph_route(xs4, ys4, fig, :orange)



end

main()