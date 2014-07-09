#KYLE PARKER
#FINAL PROGRAM
#MAY 12 2014

class Regex

	def initialize(domainname)
		@domainname = domainname
		@regular1 = Regexp.new(/(f=<|f=\?q\?<)([\w\.\+\-\=\_]+@#{@domainname})(>)/i)
		@regular2 = Regexp.new(/(t=<|t=\?q\?<)([\w\.\+\-\=\_]+@#{@domainname})(>)/i)
		@regular3 = Regexp.new(/(=<|=\?q\?<)([\w\.\+\-\=\_]+@#{@domainname})(>)/i)
	 	@discardReg = /action=discard/i
	 	@emailHash = Hash.new{|hash, key| hash[key] = {"sent" => 0, "received" => 0,"discarded" => 0, "seen" => 0}}
	end
	def parse_line(logline)
		logline.scan(@regular3){|value| @emailHash[$2.downcase]["seen"] += 1}
		if(logline =~ @discardReg)
			logline.scan(@regular2){|value| @emailHash[$2.downcase]["discarded"] += 1}
            logline.scan(@regular1){|value| @emailHash[$2.downcase]["discarded"] += 1}
		else
			logline.scan(@regular1){|value| @emailHash[$2.downcase]["sent"] += 1}
			logline.scan(@regular2){|value| @emailHash[$2.downcase]["received"] += 1}
		end	
	end
	def results()
		return @emailHash
	end
end







inputname = "tempData.txt"

stats = Regex.new('coloradomesa.edu')

 File.open(inputname, "r") do |f|
    f.each_line do |x|
        stats.parse_line(x)
    end
end


h = stats.results


key2title = { "sent" =>      "senders",
    "received" =>  "receivers",
    "discarded" => "spammed",
}

key2title.each_key do |k|
    puts "Top #{key2title[k]}:"
    h.sort{|a,b| (b[1][k] <=> a[1][k]).nonzero? || (a[0] <=> b[0]) }.select{|x| x[1][k] > 0 }.each { |x| printf "  %s: %d\n", x[0], x[1][k] }
end

