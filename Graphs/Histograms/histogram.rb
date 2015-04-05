require 'gruff'
require 'commander/import'
require 'json'

program :name, 'Histograms Drawer'
program :version, '0.1.0'
program :description, 'Execution, used for drawing histogram from given array or values'

command :draw do |c|
	c.syntax = 'draw <datafile> <imagefile>'
	c.action do |args, options|
		data = []
  		File.open(args.first).each_line {|line|
    		data.push Integer(line)
  		}
		g = Gruff::StackedBar.new
		g.bar_spacing = 0.9
		g.theme = {
			:colors => %w(orange purple green white red),
			:marker_color => '#c1c1c1',
			:background_colors => ['white', 'white', :top_bottom]
		}
		g.data :"Sources degrees", data
		g.write("#{args[1]}.png")
	end
end
