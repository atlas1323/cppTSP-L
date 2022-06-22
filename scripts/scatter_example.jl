using GLMakie

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

f = Figure()
Axis(f[1, 1])

xs = LinRange(0, 10, 20)
ys = 0.75 .*sin.(xs)

scatterlines!(xs, ys, color = :red)
scatterlines!(xs, ys .* 3, color = xs, markercolor = :blue)

f